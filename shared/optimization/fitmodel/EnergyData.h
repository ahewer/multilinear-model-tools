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
#ifndef __FIT_MODEL_ENERGY_DATA_H__
#define __FIT_MODEL_ENERGY_DATA_H__

#include <vector>

#include <armadillo>

#include "landmark/Landmark.h"

#include "model/Model.h"
#include "mesh/Mesh.h"

namespace fitModel{

/* class that contains data that is set directly and
 * does not need to be derived
 */

  class EnergyData{

  public:

    /*--------------------------------------------------------------------------*/

    EnergyData(const Model& model, const Mesh& target):
      model(model), target(target) {

      // initialize the weights to the mean weights
      this->speakerWeights = arma::vec(
        model.data().get_speaker_mode_dimension(),
        arma::fill::zeros);

      this->phonemeWeights = arma::vec(
        model.data().get_phoneme_mode_dimension(),
        arma::fill::zeros);

      this->model.convert().to_weights(
        this->speakerWeights, this->phonemeWeights);

      this->oldSpeakerWeights = this->speakerWeights;
      this->oldPhonemeWeights = this->phonemeWeights;

    }

    /*--------------------------------------------------------------------------*/

    EnergyData(const Model& model):
      model(model) {

      // initialize the weights to the mean weights
      this->speakerWeights = arma::vec(
        model.data().get_speaker_mode_dimension(),
        arma::fill::zeros);

      this->phonemeWeights = arma::vec(
        model.data().get_phoneme_mode_dimension(),
        arma::fill::zeros);

      this->model.convert().to_weights(
        this->speakerWeights, this->phonemeWeights);

      this->oldSpeakerWeights = this->speakerWeights;
      this->oldPhonemeWeights = this->phonemeWeights;

    }

    /*--------------------------------------------------------------------------*/

    const Model& model;

    // current weights
    arma::vec speakerWeights;
    arma::vec phonemeWeights;

    // old weights for evaluating the smoothness in a tracking scenario
    arma::vec oldSpeakerWeights;
    arma::vec oldPhonemeWeights;

    Mesh target;

    std::vector<Landmark> landmarks;

    /*--------------------------------------------------------------------------*/

  };
}

#endif
