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
#ifndef __LANDMARK_IO_H__
#define __LANDMARK_IO_H__

#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <armadillo>

#include <json/json.h>

#include "Landmark.h"

class LandmarkIO {

  public:

    static std::vector<Landmark> read(
        const std::string& fileName
        ) {

      std::vector<Landmark> landmarks;

      // try to open file
      std::ifstream inFile(fileName.c_str());

      // throw exception if file can not be opened
      if( inFile.is_open() == false ) {
        throw std::runtime_error("Cannot open landmarks file.");
      }

      // read json file
      Json::Value root;
      Json::Reader reader;
      reader.parse(inFile, root);

      for( Json::ArrayIndex i = 0; i < root.size(); ++i) {

        Json::Value value = root[i];

        // read the values
        std::string name = value["name"].asString();
        const double sourceX = value["sourceX"].asDouble();
        const double sourceY = value["sourceY"].asDouble();
        const double sourceZ = value["sourceZ"].asDouble();

        const double targetX = value["targetX"].asDouble();
        const double targetY = value["targetY"].asDouble();
        const double targetZ = value["targetZ"].asDouble();

        const size_t sourceIndex = value["sourceIndex"].asInt();

        const arma::vec source({sourceX, sourceY, sourceZ});
        const arma::vec target({targetX, targetY, targetZ});

        landmarks.push_back(Landmark(name, sourceIndex, source, target));

      } // end for

      inFile.close();

      return landmarks;

    } // end function

    /*-----------------------------------------------------------------------*/

    static void write(
        const std::vector<Landmark>& landmarks,
        const std::string& fileName
        ) {

      // try to open file
      std::ofstream outFile(fileName);

      // create root node of json file
      Json::Value root(Json::arrayValue);

      for(const auto& mark: landmarks) {

        Json::Value landmark(Json::objectValue);

        landmark["name"]        = Json::Value(mark.name);
        landmark["sourceIndex"] = Json::Value(mark.sourceIndex);
        landmark["sourceX"]     = Json::Value(mark.sourcePosition(0));
        landmark["sourceY"]     = Json::Value(mark.sourcePosition(1));
        landmark["sourceZ"]     = Json::Value(mark.sourcePosition(2));
        landmark["targetX"]     = Json::Value(mark.targetPosition(0));
        landmark["targetY"]     = Json::Value(mark.targetPosition(1));
        landmark["targetZ"]     = Json::Value(mark.targetPosition(2));

        root.append(landmark);

      } // end for

      Json::StyledStreamWriter writer;
      writer.write(outFile, root);

      outFile.close();

    } // end function

};
#endif
