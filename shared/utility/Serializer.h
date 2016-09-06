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
#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <vector>

#include <armadillo>

class Serializer{

public:

  /*--------------------------------------------------------------------------*/

  static arma::vec serialize(const std::vector<arma::vec>& points) {

    arma::vec result = arma::zeros(points.size() * 3);

    for(size_t i = 0; i < points.size(); ++i) {

      const arma::vec point = points.at(i);

      result(3 * i + 0) = point(0);
      result(3 * i + 1) = point(1);
      result(3 * i + 2) = point(2);

    }

    return result;

  }

  /*--------------------------------------------------------------------------*/

  static std::vector<arma::vec> unserialize(const arma::vec& serialized) {

    const size_t amount = serialized.n_elem / 3;
    std::vector<arma::vec> result;

    for(size_t i = 0; i < amount; ++i) {

      arma::vec point = arma::zeros(3);

      point(0) = serialized(i * 3 + 0);
      point(1) = serialized(i * 3 + 1);
      point(2) = serialized(i * 3 + 2);

      result.push_back(point);

    }

    return result;

  }

  /*--------------------------------------------------------------------------*/

};
#endif
