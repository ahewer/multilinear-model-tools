#ifndef __FIT_ACTION_H__
#define __FIT_ACTION_H__

#include <yaml-cpp/yaml.h>

#include "YamlMesh.h"
#include "TrackerAction.h"

class FitAction : public TrackerAction{

public:

  /*--------------------------------------------------------------------------*/

  FitAction(Tracker& tracker) : TrackerAction(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node& action) {

    this->tracker.data().currentTime =
      action["timeStamp"].as<double>();

    this->tracker.data().target =
      action["points"].as<Mesh>();

    this->tracker.fitting().apply();
    this->tracker.state().firstFrame = false;

  }

  /*--------------------------------------------------------------------------*/

};

#endif
