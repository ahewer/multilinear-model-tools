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
#ifndef __MESH_IO_H__
#define __MESH_IO_H__

#include <string>
#include <stdexcept>
#include <regex>

#include "mesh/reader/MeshReader.h"
#include "mesh/reader/ObjReader.h"
#include "mesh/reader/PlyReader.h"
#include "mesh/reader/MdlReader.h"
#include "mesh/reader/MatReader.h"

#include "mesh/writer/MeshWriter.h"
#include "mesh/writer/ObjWriter.h"
#include "mesh/writer/PlyWriter.h"



class MeshIO{
  public:

    /*---------------------------------------------------------------------------*/

    static Mesh read(const std::string& file) {
      
      std::regex regEx("[.]([[:alpha:]]+)$");
      std::smatch match;
      std::string extension;

      std::regex_search(file, match, regEx);

      extension = match[1];

      if( extension == "ply" ) {
        PlyReader reader;
        return reader.read_mesh_from(file);
      }
      else if( extension == "obj" ) {
        ObjReader reader;
        return reader.read_mesh_from(file);
      }
      else if( extension == "mdl" ) {
        MdlReader reader;
        return reader.read_mesh_from(file);
      }
      else if( extension == "mat" ) {
        MatReader reader;
        return reader.read_mesh_from(file);
      }
      else {
        throw std::runtime_error("Mesh format " + extension + " not supported.");
      }

    }

    /*---------------------------------------------------------------------------*/

    static void write(const Mesh& mesh, const std::string& file) {
      
      std::regex regEx("[.]([[:alpha:]]+)$");
      std::smatch match;
      std::string extension;

      std::regex_search(file, match, regEx);

      extension = match[1];

      if( extension == "ply" ) {
        PlyWriter writer(mesh);
        writer.write_mesh_to(file);
 
      }
      else if( extension == "obj" ) {
        ObjWriter writer(mesh);
        writer.write_mesh_to(file);
 
      }
      else {
        throw std::runtime_error("Mesh format " + extension + " not supported.");
      }

    }

    /*---------------------------------------------------------------------------*/


  private:
    MeshIO() {
    }

};
#endif
