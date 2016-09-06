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
#ifndef __FIT_MODEL_SMOOTHNESS_TERM_H__
#define __FIT_MODEL_SMOOTHNESS_TERM_H__

#include <vector>

#include <armadillo>
#include <vnl/vnl_vector.h>

#include "optimization/fitmodel/Energy.h"
#include "optimization/fitmodel/EnergyTerm.h"

namespace fitModel{

  /* class that represents the smoothness term of the energy function in a tracking
   *  scenario
   */

  class SmoothnessTerm : public EnergyTerm {

  public:

    /*--------------------------------------------------------------------------*/

    SmoothnessTerm(Energy& energy) : energy(energy) {
    }

    /*--------------------------------------------------------------------------*/

    virtual void add_energy_and_gradient(
      double& energy,
      vnl_vector<double>& gradient) const {

      // compute differences
      const arma::vec speakerDifference =
        this->energy.data().speakerWeights -
        this->energy.data().oldSpeakerWeights;

      const arma::vec phonemeDifference =
        this->energy.data().phonemeWeights -
        this->energy.data().oldPhonemeWeights;

      // get energy term weights
      const double& speakerWeight =
        this->energy.settings().weights.at("speakerSmoothnessTerm");

      const double& phonemeWeight =
        this->energy.settings().weights.at("phonemeSmoothnessTerm");

      // add energy
      energy +=
        speakerWeight *
        arma::dot(speakerDifference, speakerDifference);

      energy +=
        phonemeWeight *
        arma::dot(phonemeDifference, phonemeDifference);

      // add gradient
      for(unsigned int i = 0; i < speakerDifference.n_rows; ++i) {
        gradient[i] += 2 * speakerWeight * speakerDifference(i);
      }

      const int offset = speakerDifference.n_rows;

      for(unsigned int i = 0; i < phonemeDifference.n_rows; ++i) {
        gradient[offset + i] += 2 * phonemeWeight * phonemeDifference(i);
      }

    }

    /*--------------------------------------------------------------------------*/

  private:

    /*--------------------------------------------------------------------------*/

    Energy& energy;

    /*--------------------------------------------------------------------------*/

  };

}

#endif
