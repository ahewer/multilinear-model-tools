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
#ifndef __MODEL_WRITER_H__
#define __MODEL_WRITER_H__

#include "utility/BinaryConverter.h"

class ModelWriter{

public:

  /*--------------------------------------------------------------------------*/

  ModelWriter(const Model& model) : model(model) {

    // start the map
    this->mightyEmitter << YAML::BeginMap;

    output_dimensions();
    output_core_tensor();
    output_mean_weights();
    output_shape_space_information();

    this->mightyEmitter << YAML::EndMap;


  }

  /*--------------------------------------------------------------------------*/

  void write(const std::string& fileName) {

    std::ofstream outFile(fileName);
    outFile << this->mightyEmitter.c_str();
    outFile.close();

    // output core tensor
//    out << YAML::Key << "CoreTensor";

//    out << YAML::Value << YAML::Flow << YAML::BeginSeq;
    //   for(const double& value: coreTensor) { out << value; }
    // out << YAML::EndSeq;


  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  void output_dimensions() {

    const int dimensionPhonemeMode =
      this->model.data().get_phoneme_mode_dimension();
    const int dimensionSpeakerMode =
      this->model.data().get_speaker_mode_dimension();
    const int dimensionVertexMode =
      this->model.data().get_vertex_mode_dimension();

    const int dimensionOriginalSpeakerMode =
      this->model.data().get_original_speaker_mode_dimension();

    const int dimensionOriginalPhonemeMode =
      this->model.data().get_original_phoneme_mode_dimension();

    this->mightyEmitter << YAML::Key << "Dimensions"
                        << YAML::Value << YAML::BeginMap

                        << YAML::Key << "OriginalSpeakerMode"
                        << YAML::Value << dimensionOriginalSpeakerMode

                        << YAML::Key << "OriginalPhonemeMode"
                        << YAML::Value << dimensionOriginalPhonemeMode

                        << YAML::Key << "TruncatedSpeakerMode"
                        << YAML::Value << dimensionSpeakerMode

                        << YAML::Key << "TruncatedPhonemeMode"
                        << YAML::Value << dimensionPhonemeMode

                        << YAML::Key << "VertexMode"
                        << YAML::Value << dimensionVertexMode

                        << YAML::EndMap;

  } // end output_dimensions

  /*--------------------------------------------------------------------------*/

  void output_core_tensor() {

    const std::vector<double>& coreTensor =
      this->model.data().get_core_tensor().data().get_data();

    // convert it to binary form
    int size;
    unsigned char* bytes =
      BinaryConverter::convert_to_bytes(coreTensor, size);

    this->mightyEmitter << YAML::Key << "CoreTensor"
                        << YAML::Value << YAML::Binary(bytes, size);

    delete[] bytes;

  } // end output_core_tensor

  /*--------------------------------------------------------------------------*/

  void output_mean_weights() {

    const arma::vec& phonemeMean =
      this->model.data().get_phoneme_mean_weights();
    const arma::vec& speakerMean =
      this->model.data().get_speaker_mean_weights();

    this->mightyEmitter << YAML::Key << "MeanWeights"
                        << YAML::Value << YAML::BeginMap
                        << YAML::Key << "SpeakerMode"
                        << YAML::Value << YAML::Flow << YAML::BeginSeq;

    for(const double& value: speakerMean) {
      this->mightyEmitter << value;
    }

    this->mightyEmitter << YAML::EndSeq
                        << YAML::Key << "PhonemeMode"
                        << YAML::Value << YAML::Flow << YAML::BeginSeq;

    for(const double& value: phonemeMean) {
      this->mightyEmitter << value;
    }

    this->mightyEmitter << YAML::EndSeq
                        << YAML::EndMap;

  } // end output_mean_weights

  /*--------------------------------------------------------------------------*/

  void output_shape_space_information() {

    const arma::vec& origin =
      this->model.data().get_shape_space_origin();
    const std::vector< std::vector< unsigned int > >& faces =
      this->model.data().get_shape_space_origin_mesh().get_faces();

    this->mightyEmitter << YAML::Key << "ShapeSpace"
                        << YAML::Value << YAML::BeginMap
                        << YAML::Key << "Origin"
                        << YAML::Value << YAML::Flow << YAML::BeginSeq;

    for(const double& value: origin) {
      this->mightyEmitter << value;
    }

    this->mightyEmitter << YAML::EndSeq
                        << YAML::Key << "Faces"
                        << YAML::Value << YAML::Flow << YAML::BeginSeq;

    for(const auto& face: faces) {
      this->mightyEmitter << YAML::Flow << YAML::BeginSeq;

      for( const unsigned index: face) {
        this->mightyEmitter << index;
      } // end for face

      this->mightyEmitter << YAML::EndSeq;

    } // end for faces

    this->mightyEmitter << YAML::EndSeq
                        << YAML::EndMap;


  } // end output_shape_space_information

  /*--------------------------------------------------------------------------*/

  const Model& model;
  YAML::Emitter mightyEmitter;

  /*--------------------------------------------------------------------------*/

};

#endif
