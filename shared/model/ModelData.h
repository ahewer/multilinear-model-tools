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


private:

  /*--------------------------------------------------------------------------*/

  Tensor coreTensor;

  arma::vec shapeSpaceOrigin;
  arma::vec speakerMeanWeights;
  arma::vec phonemeMeanWeights;

  Mesh shapeSpaceOriginMesh;

  /*--------------------------------------------------------------------------*/

};

#endif
