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
#ifndef __FIT_MODEL_ENERGY_NEIGHBOR_H__
#define __FIT_MODEL_ENERGY_NEIGHBOR_H__

#include "neighborsearch/NeighborSearch.h"

#include "optimization/fitmodel/EnergyData.h"
#include "optimization/fitmodel/EnergyDerivedData.h"
#include "optimization/fitmodel/EnergySettings.h"

namespace fitModel{

  /* class for finding neighbors of the source vertices in the target vertices */
  class EnergyNeighbor{

  public:

    /*--------------------------------------------------------------------------*/

    EnergyNeighbor(
      EnergyData& energyData,
      EnergyDerivedData& energyDerivedData,
      EnergySettings& energySettings)
      : energyData(energyData),
        energyDerivedData(energyDerivedData),
        energySettings(energySettings) {

      // set target and construct kd-tree
      this->neighborSearch.set_target(this->energyData.target);
      this->areFixed = false;

      // configure search strategy
      this->neighborSearch.set_max_angle(this->energySettings.maxAngle);
      this->neighborSearch.set_max_distance(this->energySettings.maxDistance);

      // select wanted search strategy
      switch(this->energySettings.searchStrategy) {

      case EnergySettings::SearchStrategy::BASIC:
        this->searchStrategy = &(this->neighborSearch.basic());
        this->needNormals = false;
        break;

      case EnergySettings::SearchStrategy::NORMAL_PLANE:
        this->searchStrategy = &(this->neighborSearch.normal_plane());
        this->needNormals = true;
        break;

      case EnergySettings::SearchStrategy::ADAPTIVE:
        this->searchStrategy = &(this->neighborSearch.adaptive());
        this->needNormals = true;
        break;

      case EnergySettings::SearchStrategy::FIXED:
        this->searchStrategy = &(this->neighborSearch.fixed_correspondences());
        this->needNormals = false;
        this->areFixed = true;
        break;

      default:
        this->searchStrategy = &(this->neighborSearch.basic());
        this->needNormals = false;
        break;
      } // end switch

    }

    /*--------------------------------------------------------------------------*/

    /* compute neighbors according to chosen search strategy */
    void compute() {

      this->neighborSearch.set_source(this->energyDerivedData.source);

      std::vector<int> sourceIndices;
      std::vector<int> targetIndices;


      this->energyDerivedData.sourceIndices.clear();
      this->energyDerivedData.targetIndices.clear();

      this->searchStrategy->find_neighbors(
        sourceIndices,
        targetIndices
        );

      // remove indices that belong to landmarks
      for(size_t i = 0; i < sourceIndices.size(); ++i) {

        if( this->energyDerivedData.isLandmark.at(sourceIndices.at(i)) == true) {
          continue;
        }

        this->energyDerivedData.sourceIndices.push_back(sourceIndices.at(i));
        this->energyDerivedData.targetIndices.push_back(targetIndices.at(i));

      }

    }

    /*--------------------------------------------------------------------------*/

    /* helper function for updating the search structure if the target mesh
     * was changed
     */
    void update_for_target() {
      this->neighborSearch.set_target(this->energyData.target, ! this->areFixed);
    }

    /*--------------------------------------------------------------------------*/

    bool need_normals() const {
      return this->needNormals;
    }

    /*--------------------------------------------------------------------------*/

    bool are_fixed() const {
      return this->areFixed;
    }

    /*--------------------------------------------------------------------------*/

  private:

    /*--------------------------------------------------------------------------*/

    const SearchProto* searchStrategy;

    /*--------------------------------------------------------------------------*/

    bool areFixed;
    bool needNormals;
    EnergyData& energyData;
    EnergyDerivedData& energyDerivedData;
    EnergySettings& energySettings;
    NeighborSearch neighborSearch;

    /*--------------------------------------------------------------------------*/
  };

}
#endif
