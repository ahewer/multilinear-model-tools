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
#ifndef __MODEL_DATA_H__
#define __MODEL_DATA_H__

#include <armadillo>

#include "mesh/Mesh.h"
#include "tensor/Tensor.h"

class ModelData{

public:

  /*--------------------------------------------------------------------------*/

  ModelData() {
  }

  /*--------------------------------------------------------------------------*/

  /*--------------------------------------------------------------------------*/
  /* member setters */
  /*--------------------------------------------------------------------------*/

  ModelData& set_core_tensor(const Tensor& coreTensor) {

    this->coreTensor = coreTensor;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  ModelData& set_shape_space_origin(const arma::vec& origin) {

    this->shapeSpaceOrigin = origin;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  ModelData& set_shape_space_origin_mesh(const Mesh& mesh) {

    this->shapeSpaceOriginMesh = mesh;

    return *this;
  }

  /*--------------------------------------------------------------------------*/


  ModelData& set_speaker_mean_weights(const arma::vec& meanWeights) {

    this->speakerMeanWeights = meanWeights;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  ModelData& set_phoneme_mean_weights(
    const arma::vec& meanWeights) {

    this->phonemeMeanWeights = meanWeights;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  ModelData& set_original_speaker_mode_dimension(
    const int& speakerDimension
    ) {

    this->originalSpeakerModeDimension = speakerDimension;

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  ModelData& set_original_phoneme_mode_dimension(
    const int& phonemeDimension
    ) {

    this->originalPhonemeModeDimension = phonemeDimension;

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  /*--------------------------------------------------------------------------*/
  /* member getters */
  /*--------------------------------------------------------------------------*/

  /*--------------------------------------------------------------------------*/

  const Tensor& get_core_tensor() const {
    return this->coreTensor;
  }

  /*--------------------------------------------------------------------------*/

  const arma::vec& get_shape_space_origin() const {
    return this->shapeSpaceOrigin;
  }

  /*--------------------------------------------------------------------------*/

  const Mesh& get_shape_space_origin_mesh() const {
    return this->shapeSpaceOriginMesh;
  }

  /*--------------------------------------------------------------------------*/

  const arma::vec& get_speaker_mean_weights() const {
    return this->speakerMeanWeights;
  }

  /*--------------------------------------------------------------------------*/

  const arma::vec& get_phoneme_mean_weights() const {
    return this->phonemeMeanWeights;
  }

  /*--------------------------------------------------------------------------*/

  int get_speaker_mode_dimension() const {
    return this->coreTensor.data().get_mode_one_dimension();
  }

  /*--------------------------------------------------------------------------*/

  int get_phoneme_mode_dimension() const {
    return this->coreTensor.data().get_mode_two_dimension();
  }

  /*--------------------------------------------------------------------------*/

  int get_vertex_mode_dimension() const {
    return this->coreTensor.data().get_mode_three_dimension();
  }

  /*--------------------------------------------------------------------------*/

  int get_original_speaker_mode_dimension() const {
    return this->originalSpeakerModeDimension;
  }

  /*--------------------------------------------------------------------------*/

  int get_original_phoneme_mode_dimension() const {
    return this->originalPhonemeModeDimension;
  }

  /*--------------------------------------------------------------------------*/


private:

  /*--------------------------------------------------------------------------*/

  Tensor coreTensor;

  arma::vec shapeSpaceOrigin;
  arma::vec speakerMeanWeights;
  arma::vec phonemeMeanWeights;

  Mesh shapeSpaceOriginMesh;

  // original sizes of the modes before truncation was applied
  int originalSpeakerModeDimension;
  int originalPhonemeModeDimension;

  /*--------------------------------------------------------------------------*/

};

#endif
