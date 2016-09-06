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
#ifndef __YAML_MESH_H__
#define __YAML_MESH_H__

#include <yaml-cpp/yaml.h>

#include "mesh/Mesh.h"

// template implementation for turning mesh into yaml node and vice versa
namespace YAML {
  template<>
  struct convert<Mesh> {
    static Node encode(const Mesh& rhs) {
      Node node;

      const std::vector<arma::vec> vertices = rhs.get_vertices();

      for(const arma::vec& vertex : vertices) {
        node.push_back(vertex(0));
        node.push_back(vertex(1));
        node.push_back(vertex(2));
      }

      return node;
    }

    static bool decode(const Node& node, Mesh& rhs) {

      if(!node.IsSequence() || node.size() % 3 != 0) {
        return false;
      }

      std::vector<arma::vec> vertices;

      for(unsigned int i = 0; i < node.size() / 3; ++i) {

        arma::vec vertex({ node[3 * i + 0].as<double>(),
              node[3 * i + 1].as<double>(),
              node[3 * i + 2].as<double>()
              });

        vertices.push_back(vertex);

      }

      rhs.set_vertices(vertices);

      return true;
    }
  };
}

#endif
