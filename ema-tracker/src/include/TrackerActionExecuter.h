#ifndef __TRACKER_ACTION_EXECUTER_H__
#define __TRACKER_ACTION_EXECUTER_H__

#include <stdexcept>

#include <yaml-cpp/yaml.h>

#include "Tracker.h"
#include "TrackerAction.h"
#include "SetSourceIdsAction.h"
#include "ResetAction.h"
#include "FitAction.h"
#include "FixSpeakerAction.h"
#include "SetSettingsAction.h"

class TrackerActionExecuter{

public:

  /*--------------------------------------------------------------------------*/

  TrackerActionExecuter(Tracker& tracker) {

    this->actions["SET_MODEL_INDICES"] = new SetSourceIdsAction(tracker);
    this->actions["RESET"] = new ResetAction(tracker);
    this->actions["FIT"] = new FitAction(tracker);
    this->actions["FIX_SPEAKER"] = new FixSpeakerAction(tracker);
    this->actions["SET_SETTINGS"] = new SetSettingsAction(tracker);

  }

  /*--------------------------------------------------------------------------*/

  ~TrackerActionExecuter() {
    for(auto entry: this->actions) {
      delete entry.second;
    }
  }

  /*--------------------------------------------------------------------------*/

  bool execute(const YAML::Node& action) {

    const std::string actionId = action["id"].as< std::string> ();

    try{
      this->actions.at(actionId)->execute(action);
    }
    catch(std::exception& e) {
      std::cerr << "Problem executing action! Skipping." << std::endl;
      std::cerr << "Reason: " << e.what() << std::endl;

      return false;

    }

    return true;
  }

private:

  /*--------------------------------------------------------------------------*/

  std::map<std::string, TrackerAction*> actions;

  /*--------------------------------------------------------------------------*/

};

#endif
