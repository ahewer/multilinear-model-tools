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
#ifndef __BASIC_SEARCH_H__
#define __BASIC_SEARCH_H__

#include <armadillo>

#include "mesh/Mesh.h"
#include "alignment/KdTree.h"

#include "SearchProto.h"

class BasicSearch : public SearchProto {

public:

  /*-------------------------------------------------------------------------*/

  BasicSearch(
    Mesh& source,
    Mesh& target,
    KdTree*& kdTree,
    double& maxDist
    ) :
    source(source),
    target(target),
    kdTree(kdTree),
    maxDist(maxDist) {
  }

  /*-------------------------------------------------------------------------*/

  virtual void find_neighbors(
    std::vector<int>& sourceIndices,
    std::vector<int>& targetIndices
    ) const {

    sourceIndices.clear();
    targetIndices.clear();

    const std::vector<arma::vec>& sourcePoints =
      this->source.get_vertices();

    for(unsigned int sourceIndex = 0;
        sourceIndex < sourcePoints.size(); ++sourceIndex) {

      const int targetIndex =
        this->kdTree->get_nearest_neighbor_index(
          sourcePoints.at(sourceIndex)
          );

      if( is_valid(sourceIndex, targetIndex) == true ) {
        sourceIndices.push_back(sourceIndex);
        targetIndices.push_back(targetIndex);
      }

    }

  }

  /*-------------------------------------------------------------------------*/

protected:

  /*-------------------------------------------------------------------------*/

  virtual bool is_valid(
    const int& sourceIndex,
    const int& targetIndex) const {

    const arma::vec& sourcePoint =
      this->source.get_vertices().at(sourceIndex);
    const arma::vec& targetPoint =
      this->target.get_vertices().at(targetIndex);

    if( arma::norm(targetPoint - sourcePoint) < this->maxDist)  {
      return true;
    }
    else {
      return false;
    }

  }

  /*-------------------------------------------------------------------------*/

  Mesh& source;
  Mesh& target;
  KdTree*& kdTree;
  double& maxDist;

  /*-------------------------------------------------------------------------*/

};
#endif
