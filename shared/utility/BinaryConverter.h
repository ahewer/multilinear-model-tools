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
#ifndef __BINARY_CONVERTER_H__
#define __BINARY_CONVERTER_H__

#include <vector>

class BinaryConverter{

public:

  /*--------------------------------------------------------------------------*/

  static unsigned char* convert_to_bytes(
    const std::vector<double>& data, int& size) {

    // compute total size of memory storage and store in the reference
    // variable
    size = data.size() * sizeof(double);

    // allocate storage
    unsigned char* bytes = new unsigned char[size];

    // iterate over values
    for(size_t i = 0; i < data.size(); ++i) {

      // get byte access to the current value
      unsigned char* byte = (unsigned char*) &(data.at(i));

      // store all bytes
      for(size_t j = 0; j < sizeof(double); ++j) {
        bytes[sizeof(double) * i + j] = byte[j];
      } // end for j

    } // end for i

    return bytes;

  }

  /*--------------------------------------------------------------------------*/

  static std::vector<double> convert_to_double(const unsigned char* bytes, int size) {

    int valueAmount = size / sizeof(double);

    std::vector<double> values;

    for(int i = 0; i < valueAmount; ++i) {

      double value;
      unsigned char* byte = (unsigned char*) &value;

      for(size_t j = 0; j < sizeof(double); ++j) {
        byte[j] = bytes[sizeof(double) * i + j];
      }

      values.push_back(value);
    }

    return values;

  }

  /*--------------------------------------------------------------------------*/

};

#endif
