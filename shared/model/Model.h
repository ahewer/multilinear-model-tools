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
#ifndef __MODEL_H__
#define __MODEL_H__

#include "model/ModelData.h"
#include "model/ModelReconstructor.h"
#include "model/ModelMeshReconstructor.h"
#include "model/ModelConverter.h"
#include "model/ModelSpace.h"
#include "model/ModelDerivative.h"
#include "model/ModelTruncator.h"

class Model{

public:

  /*--------------------------------------------------------------------------*/

  Model() {

    this->modelConverter = nullptr;
    this->modelSpace = nullptr;
    this->modelReconstructor = nullptr;
    this->modelMeshReconstructor = nullptr;
    this->modelDerivative = nullptr;
    this->modelTruncator = nullptr;

    this->valid = false;

  }

  /*--------------------------------------------------------------------------*/

  Model(const ModelData& modelData) : modelData(modelData) {

    this->modelConverter = new ModelConverter(this->modelData);

    this->modelSpace = new ModelSpace(this->modelData);

    this->modelReconstructor = new ModelReconstructor(
        this->modelData,
        *this->modelConverter,
        *this->modelSpace
        );

    this->modelMeshReconstructor = new
      ModelMeshReconstructor(this->modelData, *this->modelReconstructor);

    this->modelDerivative = new ModelDerivative(*this->modelSpace);

    this->modelTruncator =
      new ModelTruncator(this->modelData, *this->modelSpace);

    this->valid = true;

  }

  /*--------------------------------------------------------------------------*/

  ~Model() {

    cleanup();

  }

  /*--------------------------------------------------------------------------*/

  void cleanup() {

    if(this->valid == true) {

      delete this->modelConverter;
      delete this->modelSpace;
      delete this->modelReconstructor;
      delete this->modelMeshReconstructor;
      delete this->modelDerivative;
      delete this->modelTruncator;

    }

    this->valid = false;

  }

  /*--------------------------------------------------------------------------*/

  Model(const Model& other) {

    cleanup();

    this->modelData = other.modelData;
    this->modelSpace = new ModelSpace(this->modelData);
    this->modelConverter = new ModelConverter(this->modelData);

    this->modelReconstructor = new ModelReconstructor(
      this->modelData,
      *this->modelConverter,
      *this->modelSpace
      );

    this->modelMeshReconstructor = new
      ModelMeshReconstructor(this->modelData, *this->modelReconstructor);

    this->modelDerivative = new ModelDerivative(*this->modelSpace);

    this->modelTruncator =
      new ModelTruncator(this->modelData, *this->modelSpace);

    this->valid = true;

  }

  /*--------------------------------------------------------------------------*/

  Model& operator=( const Model& other ){

    cleanup();

    this->modelData = other.modelData;
    this->modelSpace = new ModelSpace(this->modelData);
    this->modelConverter = new ModelConverter(this->modelData);

    this->modelReconstructor = new ModelReconstructor(
      this->modelData,
      *this->modelConverter,
      *this->modelSpace
      );

    this->modelMeshReconstructor = new
      ModelMeshReconstructor(this->modelData, *this->modelReconstructor);

    this->modelDerivative = new ModelDerivative(*this->modelSpace);

    this->modelTruncator =
      new ModelTruncator(this->modelData, *this->modelSpace);

    this->valid = true;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  const ModelData& data() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return this->modelData;
  }


  /*--------------------------------------------------------------------------*/

  ModelData& data() {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return this->modelData;
  }

  /*--------------------------------------------------------------------------*/


  const ModelReconstructor& reconstruct() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelReconstructor;
  }

  /*--------------------------------------------------------------------------*/

  const ModelMeshReconstructor& reconstruct_mesh() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelMeshReconstructor;
  }

  /*--------------------------------------------------------------------------*/

  const ModelConverter& convert() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelConverter;
  }

  /*--------------------------------------------------------------------------*/

  const ModelSpace& space() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelSpace;
  }

  /*--------------------------------------------------------------------------*/

  const ModelDerivative& derivative() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelDerivative;
  }

  /*--------------------------------------------------------------------------*/

  ModelTruncator& truncate() const {

    if( this->valid == false ) {
      throw std::runtime_error("Model data structures not initialized");
    }

    return *this->modelTruncator;
  }

  /*--------------------------------------------------------------------------*/


private:

  /*--------------------------------------------------------------------------*/

  ModelData modelData;
  ModelSpace* modelSpace;
  ModelReconstructor* modelReconstructor;
  ModelMeshReconstructor* modelMeshReconstructor;
  ModelConverter* modelConverter;
  ModelDerivative* modelDerivative;
  ModelTruncator* modelTruncator;

  bool valid = false;

  /*--------------------------------------------------------------------------*/

};

#endif
