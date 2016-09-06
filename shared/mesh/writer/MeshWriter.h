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
#ifndef __MESH_WRITER_H__
#define __MESH_WRITER_H__

#include <string>
#include <fstream>
#include <armadillo>

#include "mesh/Mesh.h"


class MeshWriter{
  
  public:

    MeshWriter(const Mesh& mesh) : 
      // initialize references
      vertices(mesh.get_vertices()),
      vertexNormals(mesh.get_vertex_normals()),
      vertexBoundaryMarkers(mesh.get_vertex_boundary_markers()),
      faces(mesh.get_faces()),
      faceBoundaryMarkers(mesh.get_face_boundary_markers()) {
      }

    /*-------------------------------------------------------------------------*/

    void set_comments(const std::vector<std::string>& comments) {
      this->comments = comments;
    }

    /*-------------------------------------------------------------------------*/

    virtual void write_mesh_to(const std::string& fileName) = 0; 


  protected:

    const std::vector<arma::vec>& vertices;
    const std::vector<arma::vec>& vertexNormals;
    const std::vector<bool>& vertexBoundaryMarkers;
    const std::vector< std::vector<unsigned int> > faces;
    const std::vector<bool> faceBoundaryMarkers;


    std::vector<std::string> comments;

    std::ofstream meshFile;
};
#endif
