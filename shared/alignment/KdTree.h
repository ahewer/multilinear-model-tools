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
#ifndef __KD_TREE_H__
#define __KD_TREE_H__

#include <vector>
#include <armadillo>

#include <ANN/ANN.h>

class KdTree{

  public:

    /*----------------------------------------------------------------------------*/

    KdTree() {
      this->kdTree = nullptr;
    }

    /*----------------------------------------------------------------------------*/

    KdTree(
        const std::vector<arma::vec>& points
        ) {

      this->dataPts = annAllocPts(points.size(), 3);

      for( size_t index = 0; index < points.size(); ++index) {

        this->dataPts[index][0] = points.at(index)(0);
        this->dataPts[index][1] = points.at(index)(1);
        this->dataPts[index][2] = points.at(index)(2);


      }

      this->kdTree = new ANNkd_tree(this->dataPts, points.size(), 3);
      this->points = points;

    }

    /*----------------------------------------------------------------------------*/

    ~KdTree() {
      if( this->kdTree != nullptr ) {
        annDeallocPts(dataPts);
        delete kdTree;
        this->kdTree = nullptr;
      }
    }

    /*----------------------------------------------------------------------------*/

    arma::vec get_nearest_neighbor(const arma::vec& point) const {

      const int index = get_nearest_neighbor_index(point);
      return this->points.at(index);
    }
    /*----------------------------------------------------------------------------*/

    int get_nearest_neighbor_index(const arma::vec& point) const {

      ANNpoint queryPt;
      ANNidxArray nnIdx;
      ANNdistArray dists;

      queryPt = annAllocPt(3);
      nnIdx = new ANNidx[1];
      dists = new ANNdist[1];

      nnIdx[0] = -1;

      queryPt[0] = point(0);
      queryPt[1] = point(1);
      queryPt[2] = point(2);

      kdTree->annkPriSearch(queryPt, 1, nnIdx, dists);

      const int index = nnIdx[0];

      annDeallocPt(queryPt);
      delete [] nnIdx;
      delete [] dists;

      return index;

    }

    /*----------------------------------------------------------------------------*/

    std::vector<arma::vec> get_nearest_neighbors(
      const arma::vec& point,
      const double radius) const {

      ANNpoint queryPt;
      ANNidxArray nnIdx;
      ANNdistArray dists;

      queryPt = annAllocPt(3);

      queryPt[0] = point(0);
      queryPt[1] = point(1);
      queryPt[2] = point(2);

      unsigned int k = kdTree->annkFRSearch(queryPt, radius, 0, NULL, NULL);

      nnIdx = new ANNidx[k];
      dists = new ANNdist[k];

      kdTree->annkFRSearch(queryPt, radius, k, nnIdx, dists);

      std::vector<arma::vec> result;

      for(size_t i = 0; i < k; ++i) {
        result.push_back(this->points.at(nnIdx[i]));
      }

      annDeallocPt(queryPt);
      delete [] nnIdx;
      delete [] dists;

      return result;

    }

    /*----------------------------------------------------------------------------*/

    std::vector<int> get_nearest_neighbors_index(
      const arma::vec& point,
      const double radius) const {

      ANNpoint queryPt;
      ANNidxArray nnIdx;
      ANNdistArray dists;

      queryPt = annAllocPt(3);

      queryPt[0] = point(0);
      queryPt[1] = point(1);
      queryPt[2] = point(2);

      unsigned int k = kdTree->annkFRSearch(queryPt, radius, 0, NULL, NULL);

      nnIdx = new ANNidx[k];
      dists = new ANNdist[k];

      kdTree->annkFRSearch(queryPt, radius, k, nnIdx, dists);

      std::vector<int> result;

      for(size_t i = 0; i < k; ++i) {
        result.push_back(nnIdx[i]);
      }

      annDeallocPt(queryPt);
      delete [] nnIdx;
      delete [] dists;

      return result;

    }

    /*----------------------------------------------------------------------------*/


  private:

    /*----------------------------------------------------------------------------*/

    ANNpointArray dataPts;
    ANNkd_tree* kdTree;
    std::vector<arma::vec> points;

    /*----------------------------------------------------------------------------*/

};
#endif
