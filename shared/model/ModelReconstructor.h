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
#ifndef __MODEL_RECONSTRUCTOR_H__
#define __MODEL_RECONSTRUCTOR_H__

#include <vector>

#include <armadillo>

#include "model/ModelData.h"
#include "model/ModelConverter.h"
#include "model/ModelSpace.h"

class ModelReconstructor{

public:

  /*--------------------------------------------------------------------------*/

  ModelReconstructor(
    const ModelData& modelData,
    const ModelConverter& modelConverter,
    const ModelSpace& modelSpace) :
    modelData(modelData), convert(modelConverter), space(modelSpace)  {
  }

  /*--------------------------------------------------------------------------*/

  arma::vec for_weights(
    const arma::vec& speakerWeights,
    const arma::vec& phonemeWeights
    ) const {

    const arma::mat speaker =
      this->space.speaker(speakerWeights);

    const arma::vec& origin = this->modelData.get_shape_space_origin();

    const arma::vec result =
      speaker * phonemeWeights + origin;

    return result;

  }

  /*--------------------------------------------------------------------------*/

  arma::vec for_variations(
    arma::vec speakerVariations,
    arma::vec phonemeVariations
    ) const {

    this->convert.to_weights(speakerVariations, phonemeVariations);


    return this->for_weights(speakerVariations, phonemeVariations);

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  const ModelData& modelData;
  const ModelConverter& convert;
  const ModelSpace& space;

  /*--------------------------------------------------------------------------*/
};

#endif
