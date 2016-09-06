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
#ifndef __TENSOR_DATA_H__
#define __TENSOR_DATA_H__

#include <vector>

class TensorData{

public:

  /*---------------------------------------------------------------------------*/

  TensorData() {

    this->modeOneDimension = 0;
    this->modeTwoDimension = 0;
    this->modeThreeDimension = 0;

  }

  /*---------------------------------------------------------------------------*/

  TensorData& set_data( const std::vector<double>& data ) {

    this->data = data;

    return *this;

  }

  /*---------------------------------------------------------------------------*/

  TensorData& set_mode_dimensions(
    const int& modeOne,
    const int& modeTwo,
    const int& modeThree
    ) {

    this->modeOneDimension = modeOne;
    this->modeTwoDimension = modeTwo;
    this->modeThreeDimension = modeThree;;

    return *this;
  }

  /*---------------------------------------------------------------------------*/

  int get_mode_one_dimension() const {
    return this->modeOneDimension;
  }

  /*---------------------------------------------------------------------------*/

  int get_mode_two_dimension() const {
    return this->modeTwoDimension;
  }

  /*---------------------------------------------------------------------------*/

  int get_mode_three_dimension() const {
    return this->modeThreeDimension;
  }

  /*---------------------------------------------------------------------------*/

  std::vector<double>& get_data() {
    return this->data;
  }

  /*---------------------------------------------------------------------------*/

  const std::vector<double>& get_data() const {
    return this->data;
  }

  /*---------------------------------------------------------------------------*/


private:

  /*---------------------------------------------------------------------------*/

  int modeOneDimension;
  int modeTwoDimension;
  int modeThreeDimension;

  std::vector<double> data;

  /*---------------------------------------------------------------------------*/

};

#endif
