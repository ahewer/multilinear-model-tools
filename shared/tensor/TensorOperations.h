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
#ifndef __TENSOR_OPERATIONS_H__
#define __TENSOR_OPERATIONS_H__

#include <armadillo>

#include "tensor/TensorModes.h"

class TensorOperations{

public:

  /*---------------------------------------------------------------------------*/

  TensorOperations(TensorModes& tensorModes) : tensorModes(tensorModes) {
  }

  /*---------------------------------------------------------------------------*/

  TensorOperations& mode_one_multiply(const arma::mat& matrix) {

    const arma::mat mode_one_matrix = this->tensorModes.get_mode_one_matrix();

    const arma::mat result = matrix * mode_one_matrix;

    this->tensorModes.unfold_to_mode_one_vectors(result);

    return *this;

  }

  /*---------------------------------------------------------------------------*/

  TensorOperations& mode_two_multiply(const arma::mat& matrix) {

    const arma::mat mode_two_matrix = this->tensorModes.get_mode_two_matrix();

    const arma::mat result = matrix * mode_two_matrix;

    this->tensorModes.unfold_to_mode_two_vectors(result);

    return *this;

  }

  /*---------------------------------------------------------------------------*/

  TensorOperations& mode_three_multiply(const arma::mat& matrix) {

    const arma::mat mode_three_matrix = this->tensorModes.get_mode_three_matrix();

    const arma::mat result = matrix * mode_three_matrix;

    this->tensorModes.unfold_to_mode_three_vectors(result);

    return *this;

  }

  /*---------------------------------------------------------------------------*/


private:

  /*---------------------------------------------------------------------------*/

  TensorModes& tensorModes;

  /*---------------------------------------------------------------------------*/

};

#endif
