/****
   This file is part of the multilinear-model-tools.
   These tools are meant to derive a multilinear tongue model or
   PCA palate model from mesh data and work with it.

   Some code of the multilinear-model-tools is based on
   Timo Bolkart's work on statistical analysis of human face shapes,
   cf. https://sites.google.com/site/bolkartt/

   Copyright (C) 2016 Alexander Hewer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

****/
#ifndef __FIT_MODEL_ENERGY_MINIMIZER_H__
#define __FIT_MODEL_ENERGY_MINIMIZER_H__

#include <vnl/vnl_vector.h>
#include <vnl/vnl_cost_function.h>
#include <vnl/algo/vnl_lbfgsb.h>

#include "optimization/fitmodel/Energy.h"
#include "optimization/fitmodel/EnergyFunction.h"
#include "optimization/fitmodel/DataTerm.h"
#include "optimization/fitmodel/LandmarkTerm.h"
#include "optimization/fitmodel/SmoothnessTerm.h"
#include "optimization/fitmodel/ITKWrapper.h"
#include "optimization/MinimizerSettings.h"

namespace fitModel{

  class EnergyMinimizer{

  public:

    /*--------------------------------------------------------------------------*/

    EnergyMinimizer(
      Energy& energy,
      MinimizerSettings& settings
      ) :
      energy(energy),
      settings(settings) {

      const Model& model = this->energy.data().model;

      const int dimensionSpeaker = model.data().get_speaker_mode_dimension();
      const int dimensionPhoneme = model.data().get_phoneme_mode_dimension();

      const int numWeights = dimensionSpeaker + dimensionPhoneme;

      this->weightAmount = numWeights;

      arma::vec lowerSpeaker;
      arma::vec lowerPhoneme;
      arma::vec upperSpeaker;
      arma::vec upperPhoneme;

      construct_box_boundary_weights(
        lowerSpeaker, lowerPhoneme, upperSpeaker, upperPhoneme);

      // check for PCA model
      if( dimensionSpeaker == 1 || dimensionPhoneme == 1) {
        adapt_box_to_pca(
          lowerSpeaker, lowerPhoneme, upperSpeaker, upperPhoneme);
      }

      // create needed energy terms
      this->energyTerms.push_back(new DataTerm(energy));

      if(this->energy.data().landmarks.size() > 0) {
        this->energyTerms.push_back(new LandmarkTerm(energy));
      }

      if(this->energy.settings().weights.at("speakerSmoothnessTerm") > 0 ||
         this->energy.settings().weights.at("phonemeSmoothnessTerm") > 0) {
        this->energyTerms.push_back(new SmoothnessTerm(energy));
      }

      setup_minimizer(
        lowerSpeaker, lowerPhoneme, upperSpeaker, upperPhoneme);

    }

    /*--------------------------------------------------------------------------*/

    ~EnergyMinimizer() {
      delete this->energyFunction;
      delete this->minimizer;
      for(EnergyTerm* energyTerm : this->energyTerms) {
        delete energyTerm;
      }
    }

    /*--------------------------------------------------------------------------*/

    void minimize() {

      // initialize data structures for current weights
      this->energy.update().for_weights();

      // initialize data structures for current landmarks
      this->energy.update().for_landmarks();

      // compute neighbors if fixed correspondences are used
      if(this->energy.neighbors().are_fixed() == true) {
        this->energy.neighbors().compute();
      }

      // save old weights
      this->energy.data().oldSpeakerWeights =
        this->energy.data().speakerWeights;
      this->energy.data().oldPhonemeWeights =
        this->energy.data().phonemeWeights;

      for(int i = 0; i < this->settings.iterationAmount; ++i) {
        perform_iteration();
      }

    }

    /*--------------------------------------------------------------------------*/

  private:

    /*--------------------------------------------------------------------------*/

    void perform_iteration() {

      // setup source normals if needed
      if( this->energy.neighbors().need_normals() ) {
        this->energy.update().source_normals();
      }

      // set up correspondences for current iteration if needed
      if( this->energy.neighbors().are_fixed() == false ) {
        this->energy.neighbors().compute();
      }

      // update data structures that depend on neighbors
      this->energy.update().for_neighbors();

      // use current weights as initialization
      vnl_vector<double> x(this->weightAmount, 0.);

      ITKWrapper::weights_to_vnl_vector(
        this->energy.data().speakerWeights,
        this->energy.data().phonemeWeights,
        x
        );

      // find minimizer
      this->minimizer->minimize(x);

      // set new weights
      ITKWrapper::vnl_vector_to_weights(
        x,
        this->energy.data().speakerWeights,
        this->energy.data().phonemeWeights
        );

      // update data structures depending on weights
      this->energy.update().for_weights();

    }

    /*--------------------------------------------------------------------------*/

    void construct_box_boundary_weights(
      arma::vec& lowerSpeaker,
      arma::vec& lowerPhoneme,
      arma::vec& upperSpeaker,
      arma::vec& upperPhoneme
      ) const {

      const Model& model = this->energy.data().model;

      const int dimensionSpeaker = model.data().get_speaker_mode_dimension();
      const int dimensionPhoneme = model.data().get_phoneme_mode_dimension();

      lowerSpeaker = arma::vec(dimensionSpeaker);
      lowerSpeaker.fill(-this->settings.priorSize);

      lowerPhoneme = arma::vec(dimensionPhoneme);
      lowerPhoneme.fill(-this->settings.priorSize);

      upperSpeaker = arma::vec(dimensionSpeaker);
      upperSpeaker.fill(this->settings.priorSize);

      upperPhoneme = arma::vec(dimensionPhoneme);
      upperPhoneme.fill(this->settings.priorSize);

      model.convert().to_weights(lowerSpeaker, lowerPhoneme);
      model.convert().to_weights(upperSpeaker, upperPhoneme);

    } // end construct_box_boundary_weights

    /*--------------------------------------------------------------------------*/

    // adapt box to pca model -> do not optimize mode with one entry
    void adapt_box_to_pca(
      arma::vec& lowerSpeaker,
      arma::vec& lowerPhoneme,
      arma::vec& upperSpeaker,
      arma::vec& upperPhoneme
      ) const {

      if( lowerSpeaker.n_elem == 1) {
        lowerSpeaker(0) = 1;
        upperSpeaker(0) = 1;
      }

      if( lowerPhoneme.n_elem == 1) {
        lowerPhoneme(0) = 1;
        upperPhoneme(0) = 1;
      }

    } // end adapt_box_to_pca

    /*--------------------------------------------------------------------------*/

    void setup_minimizer(
      const arma::vec& lowerSpeaker,
      const arma::vec& lowerPhoneme,
      const arma::vec& upperSpeaker,
      const arma::vec& upperPhoneme
      ) {

      const int dimensionSpeaker = lowerSpeaker.size();
      const int dimensionPhoneme = lowerPhoneme.size();

      vnl_vector<long> boundSelection(this->weightAmount, 2);
      vnl_vector<double> lowerBounds(this->weightAmount, 0.);
      vnl_vector<double> upperBounds(this->weightAmount, 0.);

      for(int i = 0; i < dimensionSpeaker; ++i) {
        lowerBounds[i] = lowerSpeaker(i);
        upperBounds[i] = upperSpeaker(i);
      }

      for(int i = 0; i < dimensionPhoneme; ++i) {
        lowerBounds[dimensionSpeaker + i] = lowerPhoneme(i);
        upperBounds[dimensionSpeaker + i] = upperPhoneme(i);
      }

      this->energyFunction = new EnergyFunction(energy, this->energyTerms);
      this->minimizer = new vnl_lbfgsb(*this->energyFunction);

      this->minimizer->set_cost_function_convergence_factor(
        this->settings.convergenceFactor
        );

      this->minimizer->set_projected_gradient_tolerance(
        this->settings.projectedGradientTolerance
        );

      this->minimizer->set_max_function_evals(
        this->settings.maxFunctionEvals
        );

      this->minimizer->set_bound_selection(boundSelection);
      this->minimizer->set_lower_bound(lowerBounds);
      this->minimizer->set_upper_bound(upperBounds);

    }

    /*--------------------------------------------------------------------------*/

    Energy& energy;

    std::vector<EnergyTerm*> energyTerms;

    MinimizerSettings& settings;

    EnergyFunction* energyFunction;

    vnl_lbfgsb* minimizer;

    int weightAmount;


    /*--------------------------------------------------------------------------*/

  };

}
#endif
