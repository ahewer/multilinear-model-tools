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
#ifndef __FIT_MODEL_ENERGY_FUNCTION_H__
#define __FIT_MODEL_ENERGY_FUNCTION_H__

#include <vnl/vnl_vector.h>
#include <vnl/vnl_cost_function.h>

#include "optimization/fitmodel/EnergyData.h"
#include "optimization/fitmodel/EnergySettings.h"
#include "optimization/fitmodel/DataTerm.h"
#include "optimization/fitmodel/LandmarkTerm.h"
#include "optimization/fitmodel/ITKWrapper.h"

namespace fitModel{

  // class used for minimizing the energy with ITK
  class EnergyFunction: public vnl_cost_function{

  public:

    /*--------------------------------------------------------------------------*/

    EnergyFunction(
      Energy& energy,
      const std::vector<EnergyTerm*>& energyTerms
      ) :
      vnl_cost_function(
        energy.data().model.data().get_speaker_mode_dimension() +
        energy.data().model.data().get_phoneme_mode_dimension()
        ),
      energy(energy),
      energyTerms(energyTerms) {

    }

    /*--------------------------------------------------------------------------*/

    virtual void compute(
      const vnl_vector<double>& x, double *f, vnl_vector<double>* g){

      // set weights
      ITKWrapper::vnl_vector_to_weights(
        x,
        this->energy.data().speakerWeights,
        this->energy.data().phonemeWeights
        );

      // update data for new weights
      this->energy.update().for_weights();

      const int speakerWeightAmount = this->energy.data().speakerWeights.size();
      const int phonemeWeightAmount = this->energy.data().phonemeWeights.size();

      // make sure that energy and gradient are reset to 0
      *f = 0;

      for(int i = 0; i < speakerWeightAmount + phonemeWeightAmount; ++i) {
        (*g)[i] = 0;
      }

      for(const EnergyTerm* term: this->energyTerms) {
        term->add_energy_and_gradient(*f, *g);
      }

    }

    /*--------------------------------------------------------------------------*/

  private:

    /*--------------------------------------------------------------------------*/

    Energy& energy;

    std::vector<EnergyTerm*> energyTerms;

    /*--------------------------------------------------------------------------*/

  };

}

#endif
