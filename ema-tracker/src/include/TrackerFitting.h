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
#ifndef __TRACKER_FITTING_H__
#define __TRACKER_FITTING_H__

#include "TrackerData.h"
#include "TrackerState.h"
#include "LiveSequenceFitting.h"

class TrackerFitting{

public:

  /*--------------------------------------------------------------------------*/

  TrackerFitting(
    TrackerData& trackerData,
    TrackerState& trackerState
    ) :
    trackerData(trackerData),
    trackerState(trackerState) {

    this->fitting = nullptr;

  }

  /*--------------------------------------------------------------------------*/

  ~TrackerFitting() {

    if(this->fitting != nullptr) {
      delete this->fitting;
    }

  }

  /*--------------------------------------------------------------------------*/

  void init() {

    if( this->fitting != nullptr) {
      delete this->fitting;
    }

    fitting = new LiveSequenceFitting(
      this->trackerData.currentModel,
      this->trackerData.settings
      );

  }

  /*--------------------------------------------------------------------------*/

  void apply() {

    if( this->trackerState.sourceIdsSet == false) {
      throw std::runtime_error("Source indices not set!");
    }

    this->fitting->fit(this->trackerData.target);

    // record speaker weights if speaker was not fixed
    if(this->trackerState.fixedSpeaker == false) {

      this->trackerData.speakerWeight =
        this->fitting->get_speaker_weights();
      this->trackerData.speakerWeights.push_back(
        this->fitting->get_speaker_weights()
        );

    }

    this->trackerData.phonemeWeight = this->fitting->get_phoneme_weights();

    // update old time
    this->trackerData.oldTime = this->trackerData.currentTime;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  TrackerData& trackerData;
  TrackerState& trackerState;

  LiveSequenceFitting* fitting;

  /*--------------------------------------------------------------------------*/

};

#endif
