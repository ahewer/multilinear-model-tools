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
#ifndef __OBJ_WRITER_H__
#define __OBJ_WRITER_H__

#include <string>
#include <vector>

#include <armadillo>

#include "mesh/writer/MeshWriter.h"

/* class for writing obj files */
class ObjWriter : public MeshWriter {

  public:

    ObjWriter(const Mesh& mesh) :
      MeshWriter(mesh) {
    }

    /*-------------------------------------------------------------------------*/

    void write_mesh_to(
      const std::string& fileName
      ) {

      this->meshFile.open(fileName);

      write_vertex_data();
      write_face_data();

      this->meshFile.close();

    }

    /*-------------------------------------------------------------------------*/

  private:

    /*-------------------------------------------------------------------------*/

    void write_comments() {

      for( const auto& comment: this->comments ) {
        this->meshFile << "# " << comment << std::endl;
      }

    }

    /*-------------------------------------------------------------------------*/

    void write_vertex(const size_t index) {

      arma::vec v = this->vertices.at(index);

      this->meshFile << "v ";
      this->meshFile << v(0) << " ";
      this->meshFile << v(1) << " ";
      this->meshFile << v(2) << std::endl;

    }

    /*-------------------------------------------------------------------------*/

    void write_vertex_normal(const size_t index) {

      if( this->vertexNormals.empty() == false ) {

        const arma::vec vn = this->vertexNormals.at(index);
        this->meshFile << "vn ";
        this->meshFile << vn(0) << " ";
        this->meshFile << vn(1) << " ";
        this->meshFile << vn(2) << std::endl;
      }

    }
 
    /*-------------------------------------------------------------------------*/

    void write_vertex_data() {

      for( size_t i = 0; i < this->vertices.size(); ++i) {

        write_vertex(i);
        write_vertex_normal(i);

      }

    }

    /*-------------------------------------------------------------------------*/

    void write_face_data() {

      for( size_t i = 0; i < this->faces.size(); ++i) {

        std::vector<unsigned int> vertexIndices = this->faces.at(i);

        this->meshFile << "f ";

        for( auto index: vertexIndices) {

          // increment, in OBJ vertex indices start at 1
          ++index;

          this->meshFile << " " << index;

          if( this->vertexNormals.empty() == false ) {
            this->meshFile << "//" << index;
          }

        }

        this->meshFile << std::endl;
      }

    }

    /*-------------------------------------------------------------------------*/

};
#endif
