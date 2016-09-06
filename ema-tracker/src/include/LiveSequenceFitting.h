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
#ifndef __LIVE_SEQUENCE_FITTING_H__
#define __LIVE_SEQUENCE_FITTING_H__

#include "mesh/Mesh.h"

#include "optimization/fitmodel/EnergyData.h"
#include "optimization/fitmodel/EnergySettings.h"
#include "optimization/fitmodel/Energy.h"
#include "optimization/fitmodel/EnergyMinimizer.h"

#include "settings.h"

class LiveSequenceFitting{

public:

  /*--------------------------------------------------------------------------*/

  LiveSequenceFitting(
    const Model& model,
    const Settings& settings) :
    energyData(model), settings(settings) {


    this->energy = new fitModel::Energy(this->energyData,
                                        this->settings.energySettings);
    this->energyMinimizer =
      new fitModel::EnergyMinimizer(*this->energy,
                                    this->settings.minimizerSettings);

    this->firstFrame = true;

    }

  /*--------------------------------------------------------------------------*/

  const arma::vec& get_speaker_weights() const {
      return this->energyData.speakerWeights;
  }

  /*--------------------------------------------------------------------------*/

  const arma::vec& get_phoneme_weights() const {
      return this->energyData.phonemeWeights;
  }

  /*--------------------------------------------------------------------------*/


  void fit(const Mesh& mesh) {

    this->energy->data().target = mesh;
    this->energy->neighbors().update_for_target();

    if( firstFrame == true ) {
      fit_first_frame();
    }
    else {
      fit_frame();
    }

    this->firstFrame = false;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void fit_first_frame() {

    const double speakerSmoothnessWeight =
      this->settings.energySettings.weights.at("speakerSmoothnessTerm");

    const double phonemeSmoothnessWeight =
      this->settings.energySettings.weights.at("phonemeSmoothnessTerm");

    // set weights to 0 for first frame
    this->settings.energySettings.weights.at("speakerSmoothnessTerm") = 0;
    this->settings.energySettings.weights.at("phonemeSmoothnessTerm") = 0;

    fit_frame();

    // restore old weights
    this->settings.energySettings.weights.at("speakerSmoothnessTerm") =
      speakerSmoothnessWeight;

    this->settings.energySettings.weights.at("phonemeSmoothnessTerm") =
      phonemeSmoothnessWeight;

    this->firstFrame = false;

  }

  /*--------------------------------------------------------------------------*/

  void fit_frame() {

    this->energyMinimizer->minimize();

    this->energyData.oldSpeakerWeights =
      this->energyData.speakerWeights;

    this->energyData.oldPhonemeWeights =
      this->energyData.phonemeWeights;


  }
  /*--------------------------------------------------------------------------*/

  fitModel::Energy* energy;
  fitModel::EnergyMinimizer* energyMinimizer;

  fitModel::EnergyData energyData;
  Settings settings;

  bool firstFrame;

  /*--------------------------------------------------------------------------*/

};

#endif
