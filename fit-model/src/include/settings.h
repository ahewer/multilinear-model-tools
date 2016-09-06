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
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "flags/FlagSingle.h"
#include "flags/FlagsParser.h"
#include "flags/FlagNone.h"

#include "optimization/fitmodel/EnergySettings.h"
#include "optimization/MinimizerSettings.h"

#include <string>

class Settings {

public:

  // input and output
  std::string target;
  std::string model;
  std::string output;
  std::string landmarks;

  MinimizerSettings minimizerSettings;
  fitModel::EnergySettings energySettings;

  bool fixedNeighbors = false;
  bool useNoProjection = false;
  bool landmarksPresent = false;
  bool useLandmarksOnlyForInitialization = false;

  Settings(int argc, char* argv[]) {

    // input and output
    FlagSingle<std::string> targetFlag("target", this->target);
    FlagSingle<std::string> modelFlag("model", this->model);
    FlagSingle<std::string> outputFlag("output", this->output);
    FlagSingle<std::string> landmarksFlag("landmarks", this->landmarks, true);

    /////////////////////////////////////////////////////////////////////////

    // minimizer settings
    FlagSingle<int> iterationAmountFlag(
      "iter", this->minimizerSettings.iterationAmount, true);
    FlagSingle<double> priorSizeFlag(
      "priorSize", this->minimizerSettings.priorSize, true);

    FlagSingle<int> convergenceFactorFlag(
      "convergenceFactor",
      this->minimizerSettings.convergenceFactor, true);

    FlagSingle<double> projectedGradientToleranceFlag(
      "projectedGradientTolerance",
      this->minimizerSettings.projectedGradientTolerance, true);

    FlagSingle<int> maxFunctionEvalsFlag(
      "maxFunctionEvals",
      this->minimizerSettings.maxFunctionEvals, true);

    /////////////////////////////////////////////////////////////////////////

    // nearest neighbor settings
    FlagSingle<double> maxDistanceFlag(
      "maxDistance", this->energySettings.maxDistance, true);

    FlagSingle<double> maxAngleFlag(
      "maxAngle", this->energySettings.maxAngle, true);

    // set default value
    this->energySettings.searchRadius = 0;
    FlagSingle<double> searchRadiusFlag(
      "searchRadius", this->energySettings.searchRadius, true);

    FlagNone fixedNeighborsFlag("fixedNeighbors", this->fixedNeighbors);
    FlagNone useNoProjectionFlag("useNoProjection", this->useNoProjection);
    FlagNone useLandmarksOnlyForInitializationFlag(
      "useLandmarksOnlyForInitialization",
      this->useLandmarksOnlyForInitialization);

    /////////////////////////////////////////////////////////////////////////

    FlagsParser parser(argv[0]);

    // input and output
    parser.define_flag(&targetFlag);
    parser.define_flag(&modelFlag);
    parser.define_flag(&outputFlag);
    parser.define_flag(&landmarksFlag);

    // minimizer settings
    parser.define_flag(&useLandmarksOnlyForInitializationFlag);
    parser.define_flag(&iterationAmountFlag);
    parser.define_flag(&priorSizeFlag);
    parser.define_flag(&convergenceFactorFlag);
    parser.define_flag(&projectedGradientToleranceFlag);
    parser.define_flag(&maxFunctionEvalsFlag);

    // nearest neighbor settings
    parser.define_flag(&maxDistanceFlag);
    parser.define_flag(&maxAngleFlag);
    parser.define_flag(&searchRadiusFlag);
    parser.define_flag(&fixedNeighborsFlag);
    parser.define_flag(&useNoProjectionFlag);

    parser.parse_from_command_line(argc, argv);

    this->energySettings.useProjection = !this->useNoProjection;

    if( this->fixedNeighbors == true) {
      this->energySettings.searchStrategy =
        fitModel::EnergySettings::SearchStrategy::FIXED;
    }
    else if( searchRadiusFlag.is_present() == true ) {
      this->energySettings.searchStrategy =
        fitModel::EnergySettings::SearchStrategy::ADAPTIVE;
    }

    this->landmarksPresent = landmarksFlag.is_present();

  }

};

#endif
