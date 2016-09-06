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
#ifndef __MODEL_TRUNCATOR_H__
#define __MODEL_TRUNCATOR_H__

class ModelTruncator{

public:

  /*--------------------------------------------------------------------------*/

  ModelTruncator(ModelData& modelData, ModelSpace& modelSpace) :
    modelData(modelData), modelSpace(modelSpace) {
  }

  /*--------------------------------------------------------------------------*/

  /*
  void speaker(const std::set<int>& indicesSpeaker) {

    std::vector<double> truncatedMeanWeights;

    for(const int& index: indicesSpeaker) {

      truncatedMeanWeights.push_back(
        this->modelData.get_speaker_mean_weights().at(index)
        );

    }

    this->modelData.get_core_tensor().truncate().mode_one(indicesSpeaker);
    this->modelData.set_speaker_mean_weights(truncatedMeanWeights);

    this->modelSpace.update();

  }
  */

  /*--------------------------------------------------------------------------*/

  /*
  void phoneme(const std::set<int>& indicesPhoneme) {

    std::vector<double> truncatedMeanWeights;

    for(const int& index: indicesPhoneme) {

      truncatedMeanWeights.push_back(
        this->modelData.get_phoneme_mean_weights().at(index)
        );

    }

    this->modelData.get_core_tensor().truncate().mode_two(indicesPhoneme);
    this->modelData.set_phoneme_mean_weights(truncatedMeanWeights);

    this->modelSpace.update();

  }
  */

  /*--------------------------------------------------------------------------*/

  /*
  // convenience version of speaker() that removes the last component
  void decrement_speaker() {

    std::set<int> indices;

    for(int i = 0; i < this->modelData.get_speaker_mode_dimension() - 1; ++i) {
      indices.insert(i);
    }

    speaker(indices);

  }
  */

  /*--------------------------------------------------------------------------*/

  /*
  // convenience version of phoneme() that removes the last component
  void decrement_phoneme() {

    std::set<int> indices;

    for(int i = 0; i < this->modelData.get_phoneme_mode_dimension() - 1; ++i) {
      indices.insert(i);
    }

    phoneme(indices);

  }
  */

  /*--------------------------------------------------------------------------*/

  void vertex(const std::set<int>& indicesVertex) {

    arma::vec truncatedShapeSpaceOrigin = arma::zeros(indicesVertex.size());

    int i = 0;

    for(const int& index: indicesVertex) {

      truncatedShapeSpaceOrigin(i) =
        this->modelData.get_shape_space_origin()(index);

      ++i;

    }

    this->modelData.get_core_tensor().truncate().mode_three(indicesVertex);
    this->modelData.set_shape_space_origin(truncatedShapeSpaceOrigin);

    this->modelSpace.update();

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  ModelData& modelData;
  ModelSpace& modelSpace;

  /*--------------------------------------------------------------------------*/

};

#endif
