#ifndef __FIX_SPEAKER_ACTION_H__
#define __FIX_SPEAKER_ACTION_H__

#include <yaml-cpp/yaml.h>
#include "TrackerAction.h"

class FixSpeakerAction : public TrackerAction{

public:

  /*--------------------------------------------------------------------------*/

  FixSpeakerAction(Tracker& tracker) : TrackerAction(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node&) {

    this->tracker.update().to_fixed_speaker();

  }

  /*--------------------------------------------------------------------------*/

};

#endif
