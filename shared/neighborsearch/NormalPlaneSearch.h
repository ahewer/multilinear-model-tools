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
#ifndef __NORMAL_PLANE_SEARCH_H__
#define __NORMAL_PLANE_SEARCH_H__

#include <armadillo>

#include "mesh/Mesh.h"
#include "alignment/KdTree.h"
#include "neighborsearch/BasicSearch.h"

class NormalPlaneSearch: public BasicSearch{

public:

  /*-------------------------------------------------------------------------*/

  NormalPlaneSearch(
    Mesh& source,
    Mesh& target,
    KdTree*& kdTree,
    double& maxDist,
    double& maxAngle
    ) :
    BasicSearch(source, target, kdTree, maxDist),
    maxAngle(maxAngle) {
  }

  /*-------------------------------------------------------------------------*/

protected:

  /*-------------------------------------------------------------------------*/

  virtual bool is_valid(
    const int& sourceIndex,
    const int& targetIndex) const {

    // get points
    const arma::vec& sourcePoint =
      this->source.get_vertices().at(sourceIndex);

    const arma::vec& targetPoint =
      this->target.get_vertices().at(targetIndex);

    // get normals
    const arma::vec& sourceNormal =
      this->source.get_vertex_normals().at(sourceIndex);

    const arma::vec& targetNormal =
      this->target.get_vertex_normals().at(targetIndex);

    const double distance = arma::norm(targetPoint - sourcePoint);

    // compute angle in degrees
    const double angle =
      acos(arma::norm_dot(sourceNormal, targetNormal)) / M_PI * 180;

    if(distance < this->maxDist && angle < this->maxAngle)  {
      return true;
    }
    else {
      return false;
    }

  }

  /*-------------------------------------------------------------------------*/

  /* inherited from BasicSearch:

  Mesh& source;
  Mesh& target;
  KdTree*& kdTree;
  double& maxDist;

  */

  double& maxAngle;

  /*-------------------------------------------------------------------------*/

};
#endif
