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
#ifndef __MODEL_MESH_RECONSTRUCTOR_H__
#define __MODEL_MESH_RECONSTRUCTOR_H__

#include <vector>
#include <armadillo>

#include "model/ModelData.h"
#include "model/ModelReconstructor.h"

class ModelMeshReconstructor{

public:

  /*--------------------------------------------------------------------------*/

  ModelMeshReconstructor(
    const ModelData& modelData,
    const ModelReconstructor& modelReconstructor) :
    modelData(modelData), reconstruct(modelReconstructor) {
  }

  /*--------------------------------------------------------------------------*/

  Mesh for_weights(
    const arma::vec& speakerWeights,
    const arma::vec& phonemeWeights
    ) const {

    return build_mesh(
      this->reconstruct.for_weights(speakerWeights, phonemeWeights)
      );

  }

  /*--------------------------------------------------------------------------*/

  Mesh for_variations(
    const arma::vec& speakerWeights,
    const arma::vec& phonemeWeights
    ) const {

    return build_mesh(
      this->reconstruct.for_variations(speakerWeights, phonemeWeights)
      );

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  Mesh build_mesh(const arma::vec values) const {

    std::vector<arma::vec> vertices;

    for(unsigned int i = 0; i < values.n_rows; i+=3) {
      arma::vec vertex({ values(i), values(i+1), values(i+2) });
      vertices.push_back(vertex);
    }

    Mesh result = this->modelData.get_shape_space_origin_mesh();

    result.set_vertices(vertices);

    return result;
  }

  /*--------------------------------------------------------------------------*/

  const ModelData& modelData;
  const ModelReconstructor& reconstruct;

  /*--------------------------------------------------------------------------*/

};

#endif
