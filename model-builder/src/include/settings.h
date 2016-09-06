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
#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "flags/FlagSingle.h"
#include "flags/FlagsParser.h"

#include <string>

class Settings {

public:

  // input and output
  std::string samples;
  std::string output;
  std::string outputMeanMeshFile;

  int truncatedSpeakerDimension;
  int truncatedPhonemeDimension;

  bool truncateSpeaker = false;
  bool truncatePhoneme = false;

  bool outputMeanMesh = false;

  Settings(int argc, char* argv[]) {


    FlagSingle<std::string> samplesFlag("samples", this->samples);
    FlagSingle<std::string> outputFlag("output", this->output);
    FlagSingle<std::string> outputMeanMeshFlag("outputMesh",
                                               this->outputMeanMeshFile,
                                               true);

    FlagSingle<int> truncatedSpeakerFlag("truncatedSpeaker",
                                         this->truncatedSpeakerDimension,
                                         true);
    FlagSingle<int> truncatedPhonemeFlag("truncatedPhoneme",
                                         this->truncatedPhonemeDimension,
                                         true);

    FlagsParser parser(argv[0]);

    // input and output
    parser.define_flag(&samplesFlag);
    parser.define_flag(&outputFlag);
    parser.define_flag(&outputMeanMeshFlag);

    parser.define_flag(&truncatedSpeakerFlag);
    parser.define_flag(&truncatedPhonemeFlag);

    parser.parse_from_command_line(argc, argv);

    this->truncateSpeaker = truncatedSpeakerFlag.is_present();
    this->truncatePhoneme = truncatedPhonemeFlag.is_present();
    this->outputMeanMesh = outputMeanMeshFlag.is_present();

  }

};

#endif
