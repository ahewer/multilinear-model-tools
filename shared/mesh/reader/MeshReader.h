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
#ifndef __MESH_READER_H__
#define __MESH_READER_H__

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "mesh/Mesh.h"

/* base class for a mesh reader */
class MeshReader {

  public:

    MeshReader() :
      // initialize references
      vertices(this->mesh.get_vertices()),
      vertexNormals(this->mesh.get_vertex_normals()),
      faces(this->mesh.get_faces()) {
      }

    virtual const Mesh& read_mesh_from( const std::string& ) = 0;

  protected:

    /*-------------------------------------------------------------------------*/

    /* helper function that reads a line and turns the result into a string */
    const std::string getline() {

      std::string read;
      std::getline(this->meshFile, read);

      ++this->lineNumber;

      return read;
    }

    /*-------------------------------------------------------------------------*/

    void throw_error(const std::string what) const {
      throw std::runtime_error(
        what + " at line " + std::to_string(this->lineNumber)
      );
    }

    /*-------------------------------------------------------------------------*/

    Mesh mesh;

    std::vector<arma::vec>& vertices;
    std::vector<arma::vec>& vertexNormals;
    std::vector< std::vector<unsigned int> >& faces;

    size_t lineNumber;
    std::ifstream meshFile;


};
#endif
