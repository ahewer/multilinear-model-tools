#ifndef __SET_SETTINGS_ACTION_H__
#define __SET_SETTINGS_ACTION_H__

#include <yaml-cpp/yaml.h>
#include "TrackerAction.h"

class SetSettingsAction : public TrackerAction {

public:

  /*--------------------------------------------------------------------------*/

  SetSettingsAction(Tracker& tracker) : TrackerAction(tracker) {
  }

  /*--------------------------------------------------------------------------*/

  virtual void execute(const YAML::Node& action) {

    fitModel::EnergySettings& energySettings =
      this->tracker.data().settings.energySettings;

    energySettings.weights["speakerSmoothnessTerm"] =
      action["speakerSmoothnessTerm"].as<double>();

    energySettings.weights["phonemeSmoothnessTerm"] =
      action["phonemeSmoothnessTerm"].as<double>();

    this->tracker.data().settings.minimizerSettings.priorSize =
      action["priorSize"].as<double>();

    this->tracker.update().for_settings();

  }

  /*--------------------------------------------------------------------------*/

};

#endif
