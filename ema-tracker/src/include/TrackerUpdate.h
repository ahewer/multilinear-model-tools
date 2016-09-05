#ifndef __TRACKER_UPDATE_H__
#define __TRACKER_UPDATE_H__

#include "TrackerData.h"
#include "TrackerState.h"
#include "TrackerFitting.h"

class TrackerUpdate{

public:

  /*--------------------------------------------------------------------------*/

  TrackerUpdate(
    TrackerData& trackerData,
    TrackerState& trackerState,
    TrackerFitting& trackerFitting
    ) :
    trackerData(trackerData),
    trackerState(trackerState),
    trackerFitting(trackerFitting) {

  }

  /*--------------------------------------------------------------------------*/

  void for_settings() {

    // reinitialize fitting object
    this->trackerFitting.init();

  }

  /*--------------------------------------------------------------------------*/

  void for_source_ids() {

    // create copy of model
    this->trackerData.currentModel =
      this->trackerData.originalModel;

    // generate list of entry indices
    std::set<int> vertexIndices;

    for(const int& id: this->trackerData.sourceIds) {

      for(int i = 0; i < 3; ++i) {
        vertexIndices.insert(3 * id + i);
      }

    }

    // truncate the model
    this->trackerData.currentModel.truncate().vertex(vertexIndices);

    // initialize fitting object
    this->trackerFitting.init();

    this->trackerState.sourceIdsSet = true;

  }

  /*--------------------------------------------------------------------------*/

  void reset() {

    this->trackerData.currentModel = this->trackerData.originalModel;
    this->trackerData.speakerWeights.clear();
    this->trackerState.sourceIdsSet = false;
    this->trackerState.fixedSpeaker = false;
    this->trackerState.firstFrame = true;

  }

  /*--------------------------------------------------------------------------*/

  void to_fixed_speaker() {

    if( this->trackerData.speakerWeights.size() == 0 ){
      std::cerr << "no previous data was fitted." << std::endl;
      return;
    }

    if( this->trackerState.sourceIdsSet == false) {
      std::cerr << "source ids are not set." << std::endl;
      return;
    }

    if( this->trackerState.fixedSpeaker == true) {
      std::cerr << "speaker already fixed." << std::endl;
    }

    // construct pca model
    set_pca_model();

    this->trackerFitting.init();

    this->trackerState.fixedSpeaker = true;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void set_pca_model() {

    const arma::vec averageSpeaker = compute_average_speaker();
    this->trackerData.currentModel = compute_pca_model(averageSpeaker);

    // set weights to average speaker
    this->trackerData.speakerWeight = averageSpeaker;

  }

  /*--------------------------------------------------------------------------*/

  arma::vec compute_average_speaker() const {

    arma::vec averageSpeaker =
      arma::zeros(
        this->trackerData.currentModel.data().get_speaker_mode_dimension());

    for(const arma::vec& speaker: this->trackerData.speakerWeights) {
      averageSpeaker += speaker;
    }

    averageSpeaker /= this->trackerData.speakerWeights.size();

    return averageSpeaker;

  }

  /*--------------------------------------------------------------------------*/

  Model compute_pca_model(const arma::vec& speakerWeights) {

    const arma::mat speakerSpace =
      this->trackerData.currentModel.space().speaker(speakerWeights);

    // construct raw data for tensor
    std::vector<double> rawData;

    const int& phonemeDimension =
      this->trackerData.currentModel.data().get_phoneme_mode_dimension();

    const int& vertexDimension =
      this->trackerData.currentModel.data().get_vertex_mode_dimension();

    for(int j = 0; j < phonemeDimension; ++j) {
      for(int i = 0; i < vertexDimension; ++i) {
        rawData.push_back(speakerSpace(i, j));
      }
    }

    // construct tensor
    // speaker mode dimension is now 1
    TensorData tensorData;
    tensorData\
      .set_data(rawData)                        \
      .set_mode_dimensions(1, phonemeDimension, vertexDimension);
    Tensor tensor(tensorData);

    // construct model
    ModelData modelData;

    modelData                                   \
      .set_core_tensor(tensor)                  \
      .set_shape_space_origin(
        this->trackerData.currentModel.data().get_shape_space_origin()
        )                                       \
      // mean weight for speaker is now 1
      .set_speaker_mean_weights(arma::vec({1})) \
      .set_phoneme_mean_weights(
        this->trackerData.currentModel.data().get_phoneme_mean_weights());

    return Model(modelData);

  } // end compute_pca_model


  /*--------------------------------------------------------------------------*/

  TrackerData& trackerData;
  TrackerState& trackerState;
  TrackerFitting& trackerFitting;

  /*--------------------------------------------------------------------------*/

};

#endif
