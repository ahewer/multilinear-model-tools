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
