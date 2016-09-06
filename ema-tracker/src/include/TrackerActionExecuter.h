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
