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
#include "optimization/MinimizerSettings.h"
#include "optimization/fitmodel/EnergySettings.h"


#include <string>


class Settings {

public:

  // input and output
  std::string model;

  int inputPort = 1234;
  int outputPort = 1235;
  int maxDataLength = 8192;
  std::string targetHost = "localhost";

  MinimizerSettings minimizerSettings;
  fitModel::EnergySettings energySettings;

  double speakerWeight = 1;
  double phonemeWeight = 1;

  Settings(int argc, char* argv[]) {

    // input
    FlagSingle<std::string> modelFlag("model", this->model);

    // network configuration
    FlagSingle<int> inputPortFlag("inputPort", this->inputPort, true);
    FlagSingle<int> outputPortFlag("outputPort", this->outputPort, true);
    FlagSingle<int> maxDataLengthFlag("maxDataLength", this->maxDataLength, true);
    FlagSingle<std::string> targetHostFlag("targetHost", this->targetHost, true);

    // smoothness for speaker and phoneme mode
    FlagSingle<double> speakerWeightFlag("speakerWeight", this->speakerWeight, true);
    FlagSingle<double> phonemeWeightFlag("phonemeWeight", this->phonemeWeight, true);

    /////////////////////////////////////////////////////////////////////////

    // minimizer settings
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


    FlagsParser parser(argv[0]);

    // input
    parser.define_flag(&modelFlag);

    // network configuration
    parser.define_flag(&inputPortFlag);
    parser.define_flag(&outputPortFlag);
    parser.define_flag(&maxDataLengthFlag);
    parser.define_flag(&targetHostFlag);

    // smoothness for speaker and phoneme mode
    parser.define_flag(&speakerWeightFlag);
    parser.define_flag(&phonemeWeightFlag);

    // minimizer settings
    parser.define_flag(&priorSizeFlag);
    parser.define_flag(&convergenceFactorFlag);
    parser.define_flag(&projectedGradientToleranceFlag);
    parser.define_flag(&maxFunctionEvalsFlag);


    parser.parse_from_command_line(argc, argv);

    // set fixed settings

    // we are not using nearest neighbor discovery -> use only one iteration
    this->minimizerSettings.iterationAmount = 1;

    // use fixed correspondences
    this->energySettings.searchStrategy =
      fitModel::EnergySettings::SearchStrategy::FIXED;

    // set weights
    this->energySettings.weights["speakerSmoothnessTerm"] = speakerWeight;
    this->energySettings.weights["phonemeSmoothnessTerm"] = phonemeWeight;

  }

};

#endif
