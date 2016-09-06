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
#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "tensor/TensorData.h"
#include "tensor/TensorAccess.h"
#include "tensor/TensorModes.h"
#include "tensor/TensorOperations.h"
#include "tensor/TensorTruncator.h"

class Tensor{

public:

  /*----------------------------------------------------------------------*/

  Tensor() {

    this->tensorAccess = nullptr;
    this->tensorModes = nullptr;
    this->tensorOperations = nullptr;
    this->tensorTruncator = nullptr;
    this->valid = false;

  }

  /*----------------------------------------------------------------------*/

  ~Tensor() {

    cleanup();

  }

  /*----------------------------------------------------------------------*/

  void cleanup() {

    if(this->valid == true) {
      delete this->tensorAccess;
      delete this->tensorModes;
      delete this->tensorOperations;
      delete this->tensorTruncator;
    }

    this->valid = false;

  }

  /*----------------------------------------------------------------------*/


  Tensor(const TensorData& data) : tensorData(data) {

    this->tensorAccess = new TensorAccess(this->tensorData);
    this->tensorModes = new TensorModes(this->tensorData, *this->tensorAccess);
    this->tensorOperations = new TensorOperations(*this->tensorModes);
    this->tensorTruncator =
      new TensorTruncator(
        this->tensorData, *this->tensorAccess);

    this->valid = true;

  }

  /*----------------------------------------------------------------------*/

  Tensor(const Tensor& tensor) : tensorData(tensor.tensorData) {

    cleanup();

    this->tensorAccess = new TensorAccess(this->tensorData);
    this->tensorModes = new TensorModes(this->tensorData, *this->tensorAccess);
    this->tensorOperations = new TensorOperations(*this->tensorModes);
    this->tensorTruncator =
      new TensorTruncator(
        this->tensorData, *this->tensorAccess);
    this->valid = true;

  }

  /*----------------------------------------------------------------------*/

  TensorData& data() {
    return this->tensorData;
  }

  /*----------------------------------------------------------------------*/

  const TensorData& data() const {
    return this->tensorData;
  }

  /*----------------------------------------------------------------------*/

  Tensor& operator=(const Tensor& other) {

    cleanup();

    this->tensorData = other.tensorData;
    this->tensorAccess = new TensorAccess(this->tensorData);
    this->tensorModes = new TensorModes(this->tensorData, *this->tensorAccess);
    this->tensorOperations = new TensorOperations(*this->tensorModes);
    this->tensorTruncator =
      new TensorTruncator(
        this->tensorData, *this->tensorAccess);

    this->valid = true;

    return *this;

  }

  /*----------------------------------------------------------------------*/

  TensorAccess& access() const {
    return *this->tensorAccess;

  }

  /*----------------------------------------------------------------------*/

  TensorModes& modes() const {
    return *this->tensorModes;
  }

  /*----------------------------------------------------------------------*/

  TensorOperations& operations() const {
    return *this->tensorOperations;
  }

  /*----------------------------------------------------------------------*/

  TensorTruncator& truncate() const {
    return *this->tensorTruncator;
  }

  /*----------------------------------------------------------------------*/

private:

  /*----------------------------------------------------------------------*/

  TensorData tensorData;
  TensorAccess* tensorAccess;
  TensorModes* tensorModes;
  TensorOperations* tensorOperations;
  TensorTruncator* tensorTruncator;

  bool valid = false;

  /*----------------------------------------------------------------------*/

};

#endif
