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
