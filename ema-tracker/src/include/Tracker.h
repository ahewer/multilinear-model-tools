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
#ifndef __TRACKER_H__
#define __TRACKER_H__

#include "TrackerData.h"
#include "TrackerState.h"
#include "TrackerFitting.h"
#include "TrackerUpdate.h"

/* composition class containing data structures relevant for the tracker */
class Tracker{

public:

  /*--------------------------------------------------------------------------*/

  Tracker(
    TrackerData& trackerData
    ) :
    trackerData(trackerData) {

    this->trackerState = new TrackerState;
    this->trackerFitting =
      new TrackerFitting(this->trackerData, *this->trackerState);
    this->trackerUpdate = new TrackerUpdate(
      this->trackerData, *this->trackerState, *this->trackerFitting);

  }

  /*--------------------------------------------------------------------------*/

  ~Tracker() {
    delete this->trackerState;
    delete this->trackerFitting;
    delete this->trackerUpdate;

  }

  /*--------------------------------------------------------------------------*/

  TrackerData& data() {
    return this->trackerData;
  }

  /*--------------------------------------------------------------------------*/

  TrackerState& state() {
    return *this->trackerState;
  }
  /*--------------------------------------------------------------------------*/

  TrackerUpdate& update() {
    return *this->trackerUpdate;
  }

  /*--------------------------------------------------------------------------*/

  TrackerFitting& fitting() {
    return *this->trackerFitting;
  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  TrackerData trackerData;
  TrackerState* trackerState;
  TrackerFitting* trackerFitting;
  TrackerUpdate* trackerUpdate;

  /*--------------------------------------------------------------------------*/

};

#endif
