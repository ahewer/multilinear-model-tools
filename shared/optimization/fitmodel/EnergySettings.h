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
#ifndef __FIT_MODEL_ENERGY_SETTINGS_H__
#define __FIT_MODEL_ENERGY_SETTINGS_H__

#include <map>

namespace fitModel{

  class EnergySettings{

  public:

    EnergySettings() {
      this->weights["dataTerm"] = 1;
      this->weights["landmarkTerm"] = 0;
      this->weights["speakerSmoothnessTerm"] = 1;
      this->weights["phonemeSmoothnessTerm"] = 1;
    }

    // should source points be projected onto the normal plane of the
    // target point?
    bool useProjection = true;

    // weights for the different energy terms
    std::map<std::string, double> weights;

    // upper bound for distance during nearest neighbor search
    double maxDistance = 5;

    // upper bound for angle between normals during nearest neighbor search
    double maxAngle = 60;

    // search radius for adaptive nearest neighbor search
    double searchRadius = 5;

    enum SearchStrategy{
      BASIC,
      NORMAL_PLANE,
      ADAPTIVE,
      FIXED
    };

    // search strategy for nearest neighbor search
    SearchStrategy searchStrategy = SearchStrategy::NORMAL_PLANE;
  };

}

#endif
