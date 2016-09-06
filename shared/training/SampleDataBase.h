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
#ifndef __SAMPLE_DATABASE_H__
#define __SAMPLE_DATABASE_H__

#include <unordered_map>
#include <set>
#include <string>

#include "mesh/Mesh.h"

class SampleDataBase{

public:

  /*----------------------------------------------------------------------*/

  void add_mesh(
    const Mesh& mesh,
    const std::string& speakerId, const std::string& phonemeId) {

    this->speakerIds.insert(speakerId);
    this->phonemeIds.insert(phonemeId);

    this->database[speakerId][phonemeId] = mesh;

  }

  /*----------------------------------------------------------------------*/

  const Mesh& get_mesh(
    const std::string& speakerId,
    const std::string& phonemeId) const {

    return this->database.at(speakerId).at(phonemeId);

  }

  /*----------------------------------------------------------------------*/

  std::vector<Mesh> get_phoneme_meshes(
    const std::string& phonemeId
    ) const {

    std::vector<Mesh> phonemeMeshes;

    for(const std::string speakerId: this->speakerIds) {
      phonemeMeshes.push_back(
        this->database.at(speakerId).at(phonemeId)
        );
    }

    return phonemeMeshes;

  }

  /*----------------------------------------------------------------------*/

  std::vector<Mesh> get_speaker_meshes(
    const std::string& speakerId
    ) const {

    std::vector<Mesh> speakerMeshes;

    for(const std::string phonemeId: this->phonemeIds) {
      speakerMeshes.push_back(
        this->database.at(speakerId).at(phonemeId)
        );
    }

    return speakerMeshes;

  }

  /*----------------------------------------------------------------------*/

  std::vector<Mesh> get_all_meshes() const {

    std::vector<Mesh> allMeshes;

    for(const std::string& speakerId: this->speakerIds) {
      for(const std::string& phonemeId: this->phonemeIds) {
        allMeshes.push_back(
          this->database.at(speakerId).at(phonemeId)
          );
      }
    }

    return allMeshes;

  }

  /*----------------------------------------------------------------------*/

  const std::set<std::string>& get_speaker_ids() const{

    return this->speakerIds;

  }

  /*----------------------------------------------------------------------*/

  const std::set<std::string>& get_phoneme_ids() const{

    return this->phonemeIds;

  }

  /*----------------------------------------------------------------------*/

  int get_speaker_amount() const {

    return this->speakerIds.size();

  }

  /*----------------------------------------------------------------------*/

  int get_phoneme_amount() const {

    return this->phonemeIds.size();
  }

  /*----------------------------------------------------------------------*/

  std::vector<std::vector< unsigned int> > get_faces() const {

    return this->database.begin()->second.begin()->second.get_faces();

  }

  /*----------------------------------------------------------------------*/

private:

  /*----------------------------------------------------------------------*/

  std::set<std::string> speakerIds;
  std::set<std::string> phonemeIds;

  std::unordered_map< std::string,
                      std::unordered_map< std::string, Mesh > > database;

  /*----------------------------------------------------------------------*/

};

#endif
