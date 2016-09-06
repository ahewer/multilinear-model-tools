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
#ifndef __SAMPLE_FILE_READER_H__
#define __SAMPLE_FILE_READER_H__

#include <yaml-cpp/yaml.h>

#include "mesh/MeshIO.h"

#include "SampleDataBase.h"

class SampleFileReader{

public:

  /*----------------------------------------------------------------------*/

  static SampleDataBase read_from(const std::string& fileName) {

    SampleDataBase database;

    YAML::Node training = YAML::LoadFile(fileName);

    // read meshes
    YAML::Node data = training["data"];

    for(const YAML::Node& speaker: data) {

      std::string speakerId = speaker["name"].as<std::string>();
      YAML::Node phonemes = speaker["phonemes"];

      for(const YAML::Node& phoneme: phonemes) {

        std::string phonemeId = phoneme["prompt"].as<std::string>();

        Mesh mesh = MeshIO::read(phoneme["path"].as<std::string>());

        database.add_mesh(mesh, speakerId, phonemeId);

      } // end phoneme
    } // end speaker

    return database;

  }

  /*----------------------------------------------------------------------*/

};

#endif
