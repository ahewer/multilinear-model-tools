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
#include <armadillo>

#include "settings.h"

#include "landmark/LandmarkIO.h"

#include "model/Model.h"
#include "model/ModelReader.h"
#include "mesh/MeshIO.h"
#include "mesh/Mesh.h"

#include "optimization/fitmodel/Energy.h"
#include "optimization/fitmodel/EnergyMinimizer.h"
#include "optimization/MinimizerSettings.h"

int main(int argc, char* argv[]) {

  Settings settings(argc, argv);

  // read input data
  Mesh target = MeshIO::read(settings.target);
  ModelReader reader(settings.model);
  Model model = reader.get_model();

  // deal with target meshes that do not provide normals
  if( settings.fixedNeighbors == false && target.has_normals() == false ) {

    // try to estimate normals if the mesh has faces
    if( target.has_faces() == true ) {
      NormalEstimation estimation(target);
      target.set_vertex_normals(estimation.compute());
    } // end if
    else {
      // use point-to-point distance measure
      settings.energySettings.searchStrategy =
        fitModel::EnergySettings::SearchStrategy::BASIC;
    } // end else

  } // end if

  fitModel::EnergyData data(model, target);

  if(settings.landmarksPresent == true) {
    data.landmarks = LandmarkIO::read(settings.landmarks);

    // use landmarks only for initialization if wanted
    if(settings.useLandmarksOnlyForInitialization == true) {

      fitModel::Energy energy(data, settings.energySettings);

      MinimizerSettings minimizerSettings = settings.minimizerSettings;

      // use one iteration
      minimizerSettings.iterationAmount = 1;
      fitModel::EnergyMinimizer minimizer(energy, minimizerSettings);

      minimizer.minimize();

      // copy weights
      data.speakerWeights = energy.data().speakerWeights;
      data.phonemeWeights = energy.data().phonemeWeights;

      // remove landmarks
      data.landmarks.clear();

    } // end if useLandmarks
  } // end if landmarksPresent

  // configure for fitting only
  settings.energySettings.weights["dataTerm"] = 1;
  settings.energySettings.weights["landmarkTerm"] = 1;

  fitModel::Energy energy(data, settings.energySettings);

  fitModel::EnergyMinimizer minimizer(energy, settings.minimizerSettings);

  minimizer.minimize();

  MeshIO::write(energy.derived_data().source, settings.output);

  return 0;

}
