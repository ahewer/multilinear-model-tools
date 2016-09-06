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
#ifndef __FIT_MODEL_ENERGY_DERIVED_DATA_H__
#define __FIT_MODEL_ENERGY_DERIVED_DATA_H__

#include <vector>
#include <map>

#include <armadillo>

#include "mesh/Mesh.h"

namespace fitModel{

/* class that represents data derived from the main data in EnergyData
 *
 * values of this class are set by EnergyDerivedDataUpdate.h
 */
  class EnergyDerivedData{

  public:

    /*--------------------------------------------------------------------------*/

    /* source mesh that depends on the chosen model parameters
     * selected in EnergyData
     */
    Mesh source;

    /* indices that represent the neighbor correspondence between
     * source and target
     */
    std::vector<int> sourceIndices;
    std::vector<int> targetIndices;

    /* linearized vertex data of source and target mesh
     *
     * only vertices belonging to the neighbor correspondences are set,
     * all other values are 0
     *
     * ATTENTION: linearizedTarget may contain points that were projected
     * onto the normal plane of the corresponding target vertex
     */
    arma::vec linearizedSource;
    arma::vec linearizedTarget;

    /* linearized data for the landmark correspondences */
    arma::vec linearizedLandmarkSource;
    arma::vec linearizedLandmarkTarget;

    /* indicators for landmark presence */
    std::vector<bool> isLandmark;

    /* weights derived from settings and current data */
    std::map<std::string, double> weights;

    /*--------------------------------------------------------------------------*/

  };
}
#endif
