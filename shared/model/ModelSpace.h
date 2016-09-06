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
#ifndef __MODEL_SPACE_H__
#define __MODEL_SPACE_H__

#include <vector>

#include <armadillo>

#include "model/ModelData.h"

class ModelSpace{

public:

  /*--------------------------------------------------------------------------*/

  ModelSpace(const ModelData& modelData) : modelData(modelData) {

    update();

  }

  /*--------------------------------------------------------------------------*/

  void update() {
    generate_model_speaker();
    generate_model_phoneme();
  }

  /*--------------------------------------------------------------------------*/

  // use speaker weights to remove this degree of freedom
  arma::mat speaker(const arma::vec& speakerWeights) const {

    // get dimensions
    const int& dimensionVertexMode =
      this->modelData.get_vertex_mode_dimension();

    const int& dimensionPhonemeMode =
      this->modelData.get_phoneme_mode_dimension();

    arma::mat speaker(
      dimensionVertexMode,
      dimensionPhonemeMode, arma::fill::zeros);

    for(unsigned int i = 0; i < modelSpeaker.size(); ++i) {
      speaker += speakerWeights(i) * modelSpeaker.at(i);
    }

    return speaker;

  }

  /*--------------------------------------------------------------------------*/

  // use phoneme weights to remove this degree of freedom
  arma::mat phoneme(const arma::vec& phonemeWeights) const {

    // get dimensions
    const int& dimensionVertexMode =
      this->modelData.get_vertex_mode_dimension();

    const int& dimensionSpeakerMode =
      this->modelData.get_speaker_mode_dimension();

    arma::mat phoneme(
      dimensionVertexMode,
      dimensionSpeakerMode, arma::fill::zeros);

    // generate space
    for(unsigned int i = 0; i < modelPhoneme.size(); ++i) {
      phoneme += phonemeWeights(i) * this->modelPhoneme.at(i);
    }

    return phoneme;

  }

  /*--------------------------------------------------------------------------*/

  void set_model_speaker(const std::vector<arma::mat>& modelSpeaker) {
    this->modelSpeaker = modelSpeaker;
  }

  /*--------------------------------------------------------------------------*/

  void set_model_phoneme(const std::vector<arma::mat>& modelPhoneme) {
    this->modelPhoneme = modelPhoneme;
  }

  /*--------------------------------------------------------------------------*/

  const std::vector<arma::mat>& get_model_speaker() const {
    return this->modelSpeaker;
  }

  /*--------------------------------------------------------------------------*/

  const std::vector<arma::mat>& get_model_phoneme() const {
    return this->modelPhoneme;
  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void generate_model_speaker() {

    this->modelSpeaker =
      this->modelData.get_core_tensor().modes().\
      get_mode_three_matrices_along_mode_one();

  }

  /*--------------------------------------------------------------------------*/

  void generate_model_phoneme() {

    this->modelPhoneme =
      this->modelData.get_core_tensor().modes().\
      get_mode_three_matrices_along_mode_two();

  }

  /*--------------------------------------------------------------------------*/

  const ModelData& modelData;

  // vector of vertexModeDimension x phonemeModeDimension matrices
  std::vector<arma::mat> modelSpeaker;

  // vector of vertexModeDimension x speakerModeDimension matrices
  std::vector<arma::mat> modelPhoneme;

  /*--------------------------------------------------------------------------*/

};
#endif
