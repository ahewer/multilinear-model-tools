#ifndef __SET_SOURCE_IDS_ACTION_H__
#define __SET_SOURCE_IDS_ACTION_H__

#include <yaml-cpp/yaml.h>
#include "TrackerAction.h"

class SetSourceIdsAction : public TrackerAction {

public:

  /*--------------------------------------------------------------------------*/

  SetSourceIdsAction(Tracker& tracker) : TrackerAction(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node& action) {

    this->tracker.data().sourceIds =
      action["indices"].as< std::vector<int> >();
    this->tracker.update().for_source_ids();

  }

  /*--------------------------------------------------------------------------*/

};

#endif
