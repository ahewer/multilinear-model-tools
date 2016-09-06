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
#ifndef __FIT_MODEL_ENERGY_H__
#define __FIT_MODEL_ENERGY_H__

#include "optimization/fitmodel/EnergyData.h"
#include "optimization/fitmodel/EnergySettings.h"
#include "optimization/fitmodel/EnergyNeighbor.h"
#include "optimization/fitmodel/EnergyDerivedData.h"
#include "optimization/fitmodel/EnergyDerivedDataUpdate.h"

namespace fitModel{

  /* composition class containing data structures relevant for the energy */
  class Energy{

  public:

    /*--------------------------------------------------------------------------*/

    Energy(
      EnergyData& energyData,
      EnergySettings& energySettings
      ) :
      energyData(energyData),
      energySettings(energySettings) {

      this->energyNeighbor =
        new EnergyNeighbor(
          this->energyData, this->energyDerivedData, this->energySettings);

      this->energyDerivedDataUpdate =
        new EnergyDerivedDataUpdate(
          this->energyData, this->energyDerivedData, this->energySettings);

    }

    /*--------------------------------------------------------------------------*/

    ~Energy() {
      delete this->energyNeighbor;
      delete this->energyDerivedDataUpdate;
    }

    /*--------------------------------------------------------------------------*/

    EnergyData& data() {
      return this->energyData;
    }

    /*--------------------------------------------------------------------------*/

    EnergyDerivedData& derived_data() {
      return this->energyDerivedData;
    }

    /*--------------------------------------------------------------------------*/

    EnergyDerivedDataUpdate& update() {
      return *this->energyDerivedDataUpdate;
    }

    /*--------------------------------------------------------------------------*/

    EnergyNeighbor& neighbors() {
      return *this->energyNeighbor;
    }

    /*--------------------------------------------------------------------------*/

    EnergySettings& settings() {
      return this->energySettings;
    }

    /*--------------------------------------------------------------------------*/

  private:

    /*--------------------------------------------------------------------------*/

    EnergyData& energyData;
    EnergyDerivedData energyDerivedData;
    EnergySettings energySettings;

    EnergyNeighbor* energyNeighbor;
    EnergyDerivedDataUpdate* energyDerivedDataUpdate;

    /*--------------------------------------------------------------------------*/

  };

}
#endif
