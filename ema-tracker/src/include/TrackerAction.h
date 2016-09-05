#ifndef __TRACKER_ACTION_H__
#define __TRACKER_ACTION_H__

#include <yaml-cpp/yaml.h>

#include "Tracker.h"

class TrackerAction{

public:

  /*--------------------------------------------------------------------------*/

  TrackerAction(Tracker& tracker) :
    tracker(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual ~TrackerAction() {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node& action) = 0;

  /*--------------------------------------------------------------------------*/

protected:

  /*--------------------------------------------------------------------------*/

  Tracker& tracker;

  /*--------------------------------------------------------------------------*/

};

#endif
