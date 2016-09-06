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
#ifndef __TRAINING_DATA_BUILDER_H__
#define __TRAINING_DATA_BUILDER_H__

#include <set>
#include <string>

#include "utility/Serializer.h"

#include "TrainingData.h"
#include "SampleDataBase.h"

class TrainingDataBuilder{

public:

  /*-----------------------------------------------------------------------*/

  TrainingDataBuilder(const SampleDataBase& database) :
    database(database) {

  }

  /*-----------------------------------------------------------------------*/

  TrainingData build() {

    init_speakers_and_phonemes();

    return create_training_data();

  } // end build

  /*-----------------------------------------------------------------------*/

  TrainingData build_without_phoneme(const std::string& phoneme) {

    init_speakers_and_phonemes();

    this->phonemes.erase(phoneme);

    return create_training_data();

  } // end build_without_phoneme


  /*-----------------------------------------------------------------------*/

  TrainingData build_without_speaker(const std::string& speaker) {

    init_speakers_and_phonemes();

    this->speakers.erase(speaker);

    return create_training_data();

  } // end build_without_speaker


  /*-----------------------------------------------------------------------*/

private:

  /*-----------------------------------------------------------------------*/

  void init_speakers_and_phonemes() {

    this->speakers = database.get_speaker_ids();
    this->phonemes = database.get_phoneme_ids();

  } // end init_speakers_and_phonemes

  /*-----------------------------------------------------------------------*/

  TrainingData create_training_data() {

    create_vectors();
    center_vectors();

    TrainingData training;
    training.mean = this->trainingMean;
    training.data = this->trainingVectors;
    training.speakerAmount = this->speakers.size();
    training.phonemeAmount = this->phonemes.size();
    training.spaceSize = this->spaceSize;

    return training;

  } // end create_training_data

  /*-----------------------------------------------------------------------*/

  void center_vectors() {

    this->trainingMean = arma::zeros(this->spaceSize);

    for( const arma::vec& vector: this->trainingVectors) {

      this->trainingMean += vector;

    }

    this->trainingMean /= this->trainingVectors.size();

    for( arma::vec& vector: this->trainingVectors) {

      vector -= this->trainingMean;

    }

  } // end center_vectors

  /*-----------------------------------------------------------------------*/

  void create_vectors() {

    this->trainingVectors.clear();

    // Mode 1: speaker
    for( const std::string& speaker : this->speakers ) {

      // Mode 2: phoneme
      for( const std::string& phoneme : this->phonemes ) {

        // get mesh
        const Mesh& mesh = database.get_mesh(speaker, phoneme);

        // serialize vertex data
        this->trainingVectors.push_back(Serializer::serialize(mesh.get_vertices()));

      } // end for phoneme

    } // end for speaker

    this->spaceSize = this->trainingVectors.at(0).n_elem;

  } // end create_vectors

  /*-----------------------------------------------------------------------*/

  arma::vec trainingMean;

  SampleDataBase database;

  std::set<std::string> speakers;
  std::set<std::string> phonemes;

  std::vector<arma::vec> trainingVectors;

  int spaceSize;

  /*-----------------------------------------------------------------------*/

};

#endif
