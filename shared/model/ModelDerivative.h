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
#ifndef __MODEL_DERIVATIVE_H__
#define __MODEL_DERIVATIVE_H__

#include <armadillo>

class ModelDerivative{

public:

  /*--------------------------------------------------------------------------*/

  ModelDerivative(const ModelSpace& modelSpace) : space(modelSpace) {
  }

  /*--------------------------------------------------------------------------*/

  // columns of returned matrix correspond to derivatives with respect to
  // the speaker weights
  arma::mat speaker(const arma::vec& phonemeWeights) const {

    return this->space.phoneme(phonemeWeights);

  }

  /*--------------------------------------------------------------------------*/

  // columns of returned matrix correspond to derivatives with respect to
  // the phoneme weights
  arma::mat phoneme(const arma::vec& speakerWeights) const {

    return this->space.speaker(speakerWeights);

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  const ModelSpace& space;

  /*--------------------------------------------------------------------------*/

};
#endif
