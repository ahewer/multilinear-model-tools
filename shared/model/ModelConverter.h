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
#ifndef __MODEL_CONVERTER_H__
#define __MODEL_CONVERTER_H__

#include <cmath>

#include <armadillo>

#include "model/ModelData.h"

class ModelConverter{

public:

  /*--------------------------------------------------------------------------*/

  ModelConverter(const ModelData& modelData): modelData(modelData) {

    this->scaleFactorSpeaker = sqrt(
      modelData.get_original_speaker_mode_dimension()
      );

    this->scaleFactorPhoneme = sqrt(
      modelData.get_original_phoneme_mode_dimension()
      );

  }

  /*--------------------------------------------------------------------------*/

  void to_weights(
    arma::vec& speakerVariations,
    arma::vec& phonemeVariations) const {

    speakerVariations /= scaleFactorSpeaker;
    speakerVariations += this->modelData.get_speaker_mean_weights();

    phonemeVariations /= scaleFactorPhoneme;
    phonemeVariations += this->modelData.get_phoneme_mean_weights();

  }

  /*--------------------------------------------------------------------------*/

  void to_variations(
    arma::vec& speakerWeights,
    arma::vec& phonemeWeights
    ) const {

    speakerWeights -= this->modelData.get_speaker_mean_weights();
    speakerWeights *= scaleFactorSpeaker;

    phonemeWeights -= this->modelData.get_phoneme_mean_weights();
    phonemeWeights *= scaleFactorPhoneme;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  const ModelData& modelData;
  double scaleFactorSpeaker;
  double scaleFactorPhoneme;

  /*--------------------------------------------------------------------------*/
};
#endif
