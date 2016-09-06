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
#ifndef __TENSOR_TRUNCATOR_H__
#define __TENSOR_TRUNCATOR_H__

#include <set>

#include "tensor/TensorData.h"
#include "tensor/TensorAccess.h"
#include "tensor/TensorModes.h"

class TensorTruncator{

public:

  /*---------------------------------------------------------------------------*/

  TensorTruncator(
    TensorData& tensorData,
    TensorAccess& tensorAccess) : tensorData(tensorData),
                                tensorAccess(tensorAccess) {
  }

  /*---------------------------------------------------------------------------*/

  /*
  void mode_one(const std::set<int>& indicesModeOne) {

    int dimensionModeTwo = this->tensorData.get_mode_two_dimension();
    int dimensionModeThree = this->tensorData.get_mode_three_dimension();

    std::set<int> indicesModeTwo;
    std::set<int> indicesModeThree;

    for(int i = 0; i < dimensionModeTwo;   ++i) { indicesModeTwo.insert(i);   }
    for(int i = 0; i < dimensionModeThree; ++i) { indicesModeThree.insert(i); }

    modes(indicesModeOne, indicesModeTwo, indicesModeThree);

  }
  */

  /*---------------------------------------------------------------------------*/

  /*
  void mode_two(const std::set<int>& indicesModeTwo) {

    int dimensionModeOne = this->tensorData.get_mode_one_dimension();
    int dimensionModeThree = this->tensorData.get_mode_three_dimension();

    std::set<int> indicesModeOne;
    std::set<int> indicesModeThree;

    for(int i = 0; i < dimensionModeOne;   ++i) { indicesModeOne.insert(i);   }
    for(int i = 0; i < dimensionModeThree; ++i) { indicesModeThree.insert(i); }

    modes(indicesModeOne, indicesModeTwo, indicesModeThree);

  }
  */

  /*---------------------------------------------------------------------------*/

  void mode_three(const std::set<int>& indicesModeThree) {

    int dimensionModeOne = this->tensorData.get_mode_one_dimension();
    int dimensionModeTwo = this->tensorData.get_mode_two_dimension();

    std::set<int> indicesModeOne;
    std::set<int> indicesModeTwo;

    for(int i = 0; i < dimensionModeOne; ++i) { indicesModeOne.insert(i); }
    for(int i = 0; i < dimensionModeTwo; ++i) { indicesModeTwo.insert(i); }

    modes(indicesModeOne, indicesModeTwo, indicesModeThree);

  }

  /*---------------------------------------------------------------------------*/


  void modes(
    const std::set<int>& indicesModeOne,
    const std::set<int>& indicesModeTwo,
    const std::set<int>& indicesModeThree
    ) {

    if(indicesModeOne.empty() ||
       indicesModeTwo.empty() ||
       indicesModeThree.empty() ) {

      throw std::runtime_error("Aborting truncation: Tensor would be empty.");

    }

    std::vector<double> newData;

    for(const int& indexModeOne: indicesModeOne) {

      for(const int& indexModeTwo: indicesModeTwo) {

        for(const int& indexModeThree: indicesModeThree ) {

          newData.push_back(
            this->tensorAccess.get_entry(
                indexModeOne, indexModeTwo, indexModeThree)
            );

        } // end for indexModeThree

      } // end for indexModeTwo

    } // end for indexModeOne

    this->tensorData.set_data(newData);

    this->tensorData.set_mode_dimensions(
      indicesModeOne.size(),
      indicesModeTwo.size(),
      indicesModeThree.size()
      );

  }

  /*---------------------------------------------------------------------------*/

private:

  /*---------------------------------------------------------------------------*/

  TensorData& tensorData;
  TensorAccess& tensorAccess;

  /*---------------------------------------------------------------------------*/

};


#endif
