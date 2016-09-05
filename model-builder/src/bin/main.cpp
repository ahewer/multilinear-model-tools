
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
