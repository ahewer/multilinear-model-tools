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
#ifndef __FIT_MODEL_ITK_WRAPPER_H__
#define __FIT_MODEL_ITK_WRAPPER_H__

#include <armadillo>
#include <vnl/vnl_vector.h>

namespace fitModel{
  /* class containing static methods from converting between ITK data structures
   * and energy data structures
   */
  class ITKWrapper{

  public:

    /*--------------------------------------------------------------------------*/

    /* converts from a vnl_vector to model weights */
    static void vnl_vector_to_weights(
      const vnl_vector<double>& x,
      arma::vec& speakerWeights,
      arma::vec& phonemeWeights
      ) {

      for(unsigned int i = 0; i < speakerWeights.size(); ++i) {
        speakerWeights(i) = x[i];
      }

      for(unsigned int i = 0; i < phonemeWeights.size(); ++i) {
        phonemeWeights(i) = x[speakerWeights.size() + i];
      }

    }

    /*--------------------------------------------------------------------------*/

    /* converts from model weights to a vnl_vector */
    static void weights_to_vnl_vector(
      const arma::vec& speakerWeights,
      const arma::vec& phonemeWeights,
      vnl_vector<double>& x
      ) {

      for(unsigned int i = 0; i < speakerWeights.size(); ++i) {
        x[i] = speakerWeights(i);
      }

      for(unsigned int i = 0; i < phonemeWeights.size(); ++i) {
        x[speakerWeights.size() + i] = phonemeWeights(i);
      }

    }

    /*--------------------------------------------------------------------------*/

  };

}
#endif
