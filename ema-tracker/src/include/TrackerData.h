#ifndef __TRACKER_DATA_H__
#define __TRACKER_DATA_H__

#include <vector>
#include <armadillo>

#include "model/Model.h"
#include "optimization/fitmodel/EnergySettings.h"

class TrackerData{

public:
  TrackerData(
    const Model& model,
    const Settings& settings
    ) : originalModel(model), currentModel(model), settings(settings) {
  }

  // current model vertex ids corresponding to the received points
  std::vector<int> sourceIds;

  // original multilinear model
  Model originalModel;

  // current model (might be truncated)
  Model currentModel;

  // current target data
  Mesh target;

  // timestamps
  double currentTime;
  double oldTime;

  // current weights
  arma::vec speakerWeight;
  arma::vec phonemeWeight;

  // speaker weights recorded over time
  std::vector<arma::vec> speakerWeights;

  // settings for fitting
  Settings settings;

};
#endif
