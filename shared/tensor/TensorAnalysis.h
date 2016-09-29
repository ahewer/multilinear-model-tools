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
#ifndef __TENSOR_ANALYSIS_H__
#define __TENSOR_ANALYSIS_H__

#include <armadillo>

class TensorAnalysis{

public:

  /*--------------------------------------------------------------------------*/

  TensorAnalysis(const Tensor& tensor) : originalTensor(tensor) {

    this->truncatedModeOneDimension =
      this->coreTensor.data().get_mode_one_dimension();
    this->truncatedModeTwoDimension =
      this->coreTensor.data().get_mode_two_dimension();

    this->analysisDone = false;

  }


  /*--------------------------------------------------------------------------*/

  void set_truncated_mode_one_dimension(const int& dimension) {

    this->analysisDone = false;
    this->truncatedModeOneDimension = dimension;

  }

  /*--------------------------------------------------------------------------*/

  void set_truncated_mode_two_dimension(const int& dimension) {

    this->analysisDone = false;
    this->truncatedModeTwoDimension = dimension;

  }

  /*--------------------------------------------------------------------------*/

  Tensor get_core_tensor() {

    perform_analysis();
    return this->coreTensor;

  }

  /*--------------------------------------------------------------------------*/

  arma::rowvec get_mode_one_mean() {

    perform_analysis();
    return this->modeOneMean;;

  }

  /*--------------------------------------------------------------------------*/

  arma::rowvec get_mode_two_mean() {

    perform_analysis();
    return this->modeTwoMean;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void perform_analysis() {

    if( this->analysisDone == false ) {

      compute_svds();
      compute_means();
      compute_core_tensor();

      this->analysisDone = true;

    } // end if

  }

  /*--------------------------------------------------------------------------*/

  void compute_svds() {

    // unfold the modes
    arma::mat modeOne = this->originalTensor.modes().get_mode_one_matrix();
    arma::mat modeTwo = this->originalTensor.modes().get_mode_two_matrix();

    // temporary variable for SVD
    arma::mat V;

    // compute left singular values of unfolded modes
    arma::svd_econ(this->modeOneU, modeOneS, V, modeOne, "left");
    arma::svd_econ(this->modeTwoU, modeTwoS, V, modeTwo, "left");

    // truncate matrices
    this->modeOneU =
      this->modeOneU.cols(0, this->truncatedModeOneDimension - 1);

    this->modeTwoU =
      this->modeTwoU.cols(0, this->truncatedModeTwoDimension - 1);

  } // end compute_svds

  /*--------------------------------------------------------------------------*/

  void compute_means() {

    this->modeOneMean = arma::sum(modeOneU, 0) / modeOneU.n_rows;
    this->modeTwoMean = arma::sum(modeTwoU, 0) / modeTwoU.n_rows;

  }

  /*--------------------------------------------------------------------------*/

  void compute_core_tensor() {

    // project tensor onto left singular values
    this->coreTensor = this->originalTensor;
    this->coreTensor.operations().mode_one_multiply(modeOneU.t())       \
      .mode_two_multiply(modeTwoU.t());

  }

  /*--------------------------------------------------------------------------*/

  Tensor originalTensor;
  Tensor coreTensor;

  // left singular vectors
  arma::mat modeOneU;
  arma::mat modeTwoU;

  // singular values
  arma::vec modeOneS;
  arma::vec modeTwoS;

  // mean values
  arma::rowvec modeOneMean;
  arma::rowvec modeTwoMean;

  /*--------------------------------------------------------------------------*/

  int truncatedModeOneDimension;
  int truncatedModeTwoDimension;

  /*--------------------------------------------------------------------------*/

  bool analysisDone;

  /*--------------------------------------------------------------------------*/

};

#endif
