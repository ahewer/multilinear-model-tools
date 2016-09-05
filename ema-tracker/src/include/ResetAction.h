#ifndef __RESET_ACTION_H__
#define __RESET_ACTION_H__

#include <yaml-cpp/yaml.h>

#include "TrackerAction.h"

class ResetAction : public TrackerAction{

public:

  /*--------------------------------------------------------------------------*/

  ResetAction(Tracker& tracker) : TrackerAction(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node&) {

    this->tracker.update().reset();

  }

  /*--------------------------------------------------------------------------*/

};

#endif
