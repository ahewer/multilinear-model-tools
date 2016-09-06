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
#ifndef __NEIGHBOR_SEARCH_H__
#define __NEIGHBOR_SEARCH_H__

#include "alignment/KdTree.h"
#include "mesh/Mesh.h"

#include "neighborsearch/BasicSearch.h"
#include "neighborsearch/NormalPlaneSearch.h"
#include "neighborsearch/AdaptiveSearch.h"
#include "neighborsearch/FixedCorrespondences.h"

class NeighborSearch{

public:

  /*--------------------------------------------------------------------------*/

  NeighborSearch() {

    this->kdTree = nullptr;

    this->searchRadius = 4;
    this->maxDist = 5;
    this->maxAngle = 60;

    this->basicSearch = new BasicSearch(
      this->source,
      this->target,
      this->kdTree,
      this->maxDist
      );

    this->normalPlaneSearch = new NormalPlaneSearch(
      this->source,
      this->target,
      this->kdTree,
      this->maxDist,
      this->maxAngle
      );

    this->adaptiveSearch = new AdaptiveSearch(
      this->source,
      this->target,
      this->kdTree,
      this->maxDist,
      this->maxAngle,
      this->searchRadius
      );

    this->fixedCorrespondences = new FixedCorrespondences(
      this->source,
      this->target
      );

  }

  /*--------------------------------------------------------------------------*/

  ~NeighborSearch() {

    delete this->kdTree;
    delete this->basicSearch;
    delete this->normalPlaneSearch;
    delete this->adaptiveSearch;
    delete this->fixedCorrespondences;

  }

  /*--------------------------------------------------------------------------*/

  NeighborSearch& set_search_radius(const double& radius) {

    this->searchRadius = radius;

    return *this;
  }

  /*--------------------------------------------------------------------------*/

  NeighborSearch& set_source(const Mesh& source) {

    this->source = source;

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  NeighborSearch& set_target(const Mesh& target, bool computeKdTree = true) {

    this->target = target;

    if(computeKdTree == true) {

      if(this->kdTree != nullptr) {
        delete this->kdTree;
      }

      this->kdTree = new KdTree(target.get_vertices());

    }

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  NeighborSearch& set_max_distance(const double& maxDist) {

    this->maxDist = maxDist;

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  NeighborSearch& set_max_angle(const double& maxAngle) {

    this->maxAngle = maxAngle;

    return *this;

  }

  /*--------------------------------------------------------------------------*/

  const BasicSearch& basic() const {

    return *this->basicSearch;

  }

  /*--------------------------------------------------------------------------*/

  const AdaptiveSearch& adaptive() const {

    return *this->adaptiveSearch;

  }

  /*--------------------------------------------------------------------------*/

  const NormalPlaneSearch& normal_plane() const {

    return *this->normalPlaneSearch;

  }

  /*--------------------------------------------------------------------------*/

  const FixedCorrespondences& fixed_correspondences() const {

    return *this->fixedCorrespondences;
  }

  /*--------------------------------------------------------------------------*/


private:

  /*--------------------------------------------------------------------------*/

  double maxDist;
  double maxAngle;
  double searchRadius;

  Mesh source;
  Mesh target;

  KdTree* kdTree;

  BasicSearch* basicSearch;
  NormalPlaneSearch* normalPlaneSearch;
  AdaptiveSearch* adaptiveSearch;
  FixedCorrespondences* fixedCorrespondences;

  /*--------------------------------------------------------------------------*/

};

#endif
