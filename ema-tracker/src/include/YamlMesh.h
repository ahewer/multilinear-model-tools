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
