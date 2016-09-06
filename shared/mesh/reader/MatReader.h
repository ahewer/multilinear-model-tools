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
#ifndef __MAT_READER_H__
#define __MAT_READER_H__

#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <regex>

#include <armadillo>

#include "mesh/reader/MeshReader.h"

/* class for reading mat files */
class MatReader : public MeshReader {

  public:

    MatReader() :
      MeshReader() {
      }

    /*-------------------------------------------------------------------------*/

    Mesh& read_mesh_from(const std::string& fileName) {

      // clear mesh
      this->mesh = Mesh();

      this->meshFile.open(fileName);

      if(this->meshFile.is_open() == false ) {
        throw std::runtime_error("Cannot open file " + fileName + ".");
      }

      read_vertex_data();

      this->meshFile.close();

      return this->mesh;

    }

    /*-------------------------------------------------------------------------*/

  private:


    /*-------------------------------------------------------------------------*/

    /* read vertex data */
    void read_vertex_data() {

      while(!this->meshFile.eof()) {
        std::string line = getline();

        std::stringstream lineStream(line);
        read_vertex(lineStream);
      }

    }

    /*-------------------------------------------------------------------------*/
    void read_vertex( std::stringstream& stream) {

      double x, y, z;

      stream >> x;
      stream >> y;
      stream >> z;

      arma::vec vertex({x, 240-z, 24+y});

      this->vertices.push_back(vertex);

    }

    /*-------------------------------------------------------------------------*/
 
};
#endif
