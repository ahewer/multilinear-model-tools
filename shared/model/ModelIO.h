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
#ifndef __MODEL_IO_H__
#define __MODEL_IO_H__

#include <string>
#include <fstream>

#include <json/json.h>
#include <armadillo>

#include "model/reader/RestrictedModelReader.h"
//#include "model/reader/ModelReader.h"

class ModelIO{

public:

  static Model read_from(const std::string& fileName) {

      std::regex regEx("[.]([[:alpha:]]+)$");
      std::smatch match;
      std::string extension;

      std::regex_search(fileName, match, regEx);

      extension = match[1];

      if( extension == "rmm" ) {
        RestrictedModelReader reader;
        return reader.read_from(fileName);
      }
/*      else if( extension == "mm" ) {
        ModelReader reader;
        return reader.read_from(file);
      }
*/
      else {
        throw std::runtime_error("Model format " + extension + " not supported.");
      }

  }

};

#endif
