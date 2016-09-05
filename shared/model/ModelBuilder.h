#ifndef __MODEL_BUILDER_H__
#define __MODEL_BUILDER_H__

#include <stdexcept>

#include <armadillo>

#include "model/ModelData.h"
#include "model/Model.h"

#include "tensor/Tensor.h"
#include "tensor/TensorAnalysis.h"

#include "utility/Serializer.h"

#include "mesh/Mesh.h"

class ModelBuilder{

public:

  /*--------------------------------------------------------------------------*/

  ModelBuilder() {

    this->tensorSet = false;
    this->originSet = false;
    this->facesSet = false;

  }

  /*--------------------------------------------------------------------------*/

  void set_tensor(const Tensor& tensor) {

    this->tensor = tensor;
    this->truncatedSpeakerModeDimension =
      this->tensor.data().get_mode_one_dimension();

    this->truncatedPhonemeModeDimension =
      this->tensor.data().get_mode_two_dimension();

    this->tensorSet = true;

  }

  /*--------------------------------------------------------------------------*/

  void set_origin(const arma::vec& origin) {

    this->origin = origin;
    this->originSet = true;

  }

  /*--------------------------------------------------------------------------*/

  void set_faces(
    const std::vector< std::vector<unsigned int> > faces) {

    this->faces = faces;
    this->facesSet = true;

  }

  /*--------------------------------------------------------------------------*/

  void set_truncated_speaker_mode_dimension(const int& truncatedDimension) {

    this->truncatedSpeakerModeDimension = truncatedDimension;

  }

  /*--------------------------------------------------------------------------*/

  void set_truncated_phoneme_mode_dimension(const int& truncatedDimension) {

    this->truncatedPhonemeModeDimension = truncatedDimension;

  }

  /*--------------------------------------------------------------------------*/


  Model build() {

    // verify that necessary data is present
    verify();

    construct_origin_mesh();

    TensorAnalysis analysis(this->tensor);

    analysis.set_truncated_mode_one_dimension(
      this->truncatedSpeakerModeDimension
      );

    analysis.set_truncated_mode_two_dimension(
      this->truncatedPhonemeModeDimension
      );

    Tensor coreTensor = analysis.get_core_tensor();
    arma::rowvec speakerMeanWeights = analysis.get_mode_one_mean();
    arma::rowvec phonemeMeanWeights = analysis.get_mode_two_mean();

    ModelData modelData;
    modelData.set_core_tensor(coreTensor)                   \
      .set_shape_space_origin(this->origin)                   \
      .set_shape_space_origin_mesh(this->originMesh)          \
      .set_speaker_mean_weights(speakerMeanWeights.t())       \
      .set_phoneme_mean_weights(phonemeMeanWeights.t());

    return Model(modelData);

  }

  /*--------------------------------------------------------------------------*/

  void construct_origin_mesh() {

    this->originMesh.set_vertices(Serializer::unserialize(this->origin));
    this->originMesh.set_faces(this->faces);

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void verify() {

    if( !(this->tensorSet && this->facesSet && this->originSet) ) {

      throw std::logic_error(
        "Can not build model. Necessary data is not present.");

    } // end if

  }

  /*--------------------------------------------------------------------------*/

  Mesh originMesh;

  Tensor tensor;

  arma::vec origin;
  std::vector< std::vector<unsigned int> > faces;

  /*--------------------------------------------------------------------------*/

  bool tensorSet;
  bool originSet;
  bool facesSet;

  /*--------------------------------------------------------------------------*/

  int truncatedSpeakerModeDimension;
  int truncatedPhonemeModeDimension;

  /*--------------------------------------------------------------------------*/

};

#endif
