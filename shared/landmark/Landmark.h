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
#ifndef __LANDMARK_H__
#define __LANDMARK_H__

#include <armadillo>

struct Landmark{

  Landmark() {
    this->sourceIndex = -1;
    this->sourcePosition = arma::zeros<arma::vec> (3);
    this->targetPosition = arma::zeros<arma::vec> (3);
  }

  Landmark(
      const int& sourceIndex,
      const arma::vec& sourcePosition,
      const arma::vec& targetPosition
      ) :
    sourceIndex(sourceIndex),
    sourcePosition(sourcePosition),
    targetPosition(targetPosition) {
    }

  Landmark(
      const std::string& name,
      const int& sourceIndex,
      const arma::vec& sourcePosition,
      const arma::vec& targetPosition
      ) :
    name(name),
    sourceIndex(sourceIndex),
    sourcePosition(sourcePosition),
    targetPosition(targetPosition) {
    }


  std::string name;
  int sourceIndex;
  arma::vec sourcePosition;
  arma::vec targetPosition;
};
#endif
