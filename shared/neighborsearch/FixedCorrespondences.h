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
#ifndef __FIXED_CORRESPONDENCES_H__
#define __FIXED_CORRESPONDENCES_H__

#include "mesh/Mesh.h"
#include "neighborsearch/SearchProto.h"

class FixedCorrespondences : public SearchProto{

public:

  /*-------------------------------------------------------------------------*/

  FixedCorrespondences(
    Mesh& source,
    Mesh& target
    ) :
    source(source), target(target)
    {

  }

  /*-------------------------------------------------------------------------*/

  virtual void find_neighbors(
    std::vector<int>& sourceIndices,
    std::vector<int>& targetIndices
    ) const {

    sourceIndices.clear();
    targetIndices.clear();

    if(this->source.get_vertices().size() != this->target.get_vertices().size()) {
      throw std::runtime_error(
        "Cannot use fixed correspondences, meshes have different sizes.\nSource: "
        + std::to_string(this->source.get_vertices().size()) + " != Target : "
        + std::to_string(this->target.get_vertices().size())
        );
    }

    // create one to one correspondence
    for(unsigned int index = 0; index < this->source.get_vertices().size();
        ++index) {
      sourceIndices.push_back(index);
      targetIndices.push_back(index);
    }

  }

  /*-------------------------------------------------------------------------*/

private:

  /*-------------------------------------------------------------------------*/

  Mesh& source;
  Mesh& target;

  std::vector<int> indices;

  /*-------------------------------------------------------------------------*/

};
#endif
