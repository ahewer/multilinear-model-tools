#ifndef __TRACKER_FITTING_H__
#define __TRACKER_FITTING_H__

#include "TrackerData.h"
#include "TrackerState.h"
#include "LiveSequenceFitting.h"

class TrackerFitting{

public:

  /*--------------------------------------------------------------------------*/

  TrackerFitting(
    TrackerData& trackerData,
    TrackerState& trackerState
    ) :
    trackerData(trackerData),
    trackerState(trackerState) {

    this->fitting = nullptr;

  }

  /*--------------------------------------------------------------------------*/

  ~TrackerFitting() {

    if(this->fitting != nullptr) {
      delete this->fitting;
    }

  }

  /*--------------------------------------------------------------------------*/

  void init() {

    if( this->fitting != nullptr) {
      delete this->fitting;
    }

    fitting = new LiveSequenceFitting(
      this->trackerData.currentModel,
      this->trackerData.settings
      );

  }

  /*--------------------------------------------------------------------------*/

  void apply() {

    if( this->trackerState.sourceIdsSet == false) {
      throw std::runtime_error("Source indices not set!");
    }

    // do not fit old frames
    if(this->trackerData.oldTime > this->trackerData.currentTime &&
       this->trackerState.firstFrame == false) {

      return;

    }

    this->fitting->fit(this->trackerData.target);

    // record speaker weights if speaker was not fixed
    if(this->trackerState.fixedSpeaker == false) {

      this->trackerData.speakerWeight =
        this->fitting->get_speaker_weights();
      this->trackerData.speakerWeights.push_back(
        this->fitting->get_speaker_weights()
        );

    }

    this->trackerData.phonemeWeight = this->fitting->get_phoneme_weights();

    // update old time
    this->trackerData.oldTime = this->trackerData.currentTime;

  }

  /*--------------------------------------------------------------------------*/

private:

  /*--------------------------------------------------------------------------*/

  TrackerData& trackerData;
  TrackerState& trackerState;

  LiveSequenceFitting* fitting;

  /*--------------------------------------------------------------------------*/

};

#endif
