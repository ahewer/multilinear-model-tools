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

#include "mesh/MeshIO.h"

#include "tensor/Tensor.h"
#include "tensor/TensorBuilder.h"

#include "training/SampleFileReader.h"
#include "training/TrainingDataBuilder.h"

#include "model/Model.h"
#include "model/ModelBuilder.h"
#include "model/ModelWriter.h"

#include "settings.h"

int main(int argc, char* argv[]){

  Settings settings(argc, argv);

  SampleDataBase database = SampleFileReader::read_from(settings.samples);
  TrainingDataBuilder trainingBuilder(database);

  TrainingData data = trainingBuilder.build();

  auto tensor = TensorBuilder::build_tensor(data);

  ModelBuilder builder;

  builder.set_faces(database.get_faces());
  builder.set_tensor(tensor);
  builder.set_origin(data.mean);

  if( settings.truncateSpeaker ) {
    builder.set_truncated_speaker_mode_dimension(settings.truncatedSpeakerDimension);
  }

  if( settings.truncatePhoneme ) {
    builder.set_truncated_phoneme_mode_dimension(settings.truncatedPhonemeDimension);
  }

  Model model = builder.build();

  ModelWriter writer(model);
  writer.write(settings.output);

  if( settings.outputMeanMesh ) {
    MeshIO::write(model.data().get_shape_space_origin_mesh(), settings.outputMeanMeshFile);
  }

  return 0;

}
