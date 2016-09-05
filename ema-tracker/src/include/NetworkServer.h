#ifndef __NETWORK_SERVER_H__
#define __NETWORK_SERVER_H__

#include <chrono>
#include <future>
#include <stack>
#include <queue>
#include <string>

#include <armadillo>
#include <json/json.h>
#include <asio.hpp>

#include "Tracker.h"
#include "TrackerActionExecuter.h"
#include "TrackerAction.h"


class NetworkServer{

public:

  /*-------------------------------------------------------------------------*/

  NetworkServer(
    Tracker& tracker,
    Settings settings
    ) :
    tracker(tracker),
    settings(settings),
    trackerActionExecuter(this->tracker) {

  }

  /*-------------------------------------------------------------------------*/

  /* thread function for receiving data */
  void read() {

    asio::io_service ioService;

    asio::ip::udp::socket socket(ioService,
                      asio::ip::udp::endpoint(asio::ip::udp::v4(),
                                          this->settings.inputPort));

    while(true) {

      // initialize everything to 0
      char data[8192] = {0};
      asio::ip::udp::endpoint senderEndpoint;
      socket.receive_from(
        asio::buffer(data, this->settings.maxDataLength), senderEndpoint
        );

      process(data);

    }

  } // end read

  /*-------------------------------------------------------------------------*/

  void execute_actions() {

    while(true) {

      this->managementMutex.lock();
      int actionAmount = this->managementActions.size();
      this->managementMutex.unlock();

      // always take care of all management actions
      while(actionAmount > 0) {

        this->managementMutex.lock();

        YAML::Node action = this->managementActions.top();
        this->managementActions.pop();
        actionAmount = this->managementActions.size();

        this->managementMutex.unlock();
        this->trackerActionExecuter.execute(action);

      }

      // now turn to fitting action
      if( newFit == false ) {
        continue;
      }

      this->fitMutex.lock();

      YAML::Node action = this->fitAction;
      this->newFit = false;

      this->fitMutex.unlock();

      if(this->trackerActionExecuter.execute(action)) {

        // send result
        send_result(
          convert_to_json_string(
            this->tracker.data().speakerWeight,
            this->tracker.data().phonemeWeight
            )
          );

      }

    } // end while

  } // end execute_actions

  /*-------------------------------------------------------------------------*/

  void run() {

      auto readingThread =
        std::async(std::launch::async, &NetworkServer::read, this);

      auto executeActionsThread =
        std::async(std::launch::async, &NetworkServer::execute_actions, this);

  } // end run

  /*-------------------------------------------------------------------------*/

private:

  /*-------------------------------------------------------------------------*/

  /* processes the received data */

  void process(char* data) {

    std::string actionString(data);
    YAML::Node action = YAML::Load(actionString);

    // all actions not performing a fit are considered as management actions
    if( action["id"].as<std::string>() != "FIT" ) {

      this->managementMutex.lock();
      this->managementActions.push(action);
      this->managementMutex.unlock();

    }
    else{

      this->fitMutex.lock();
      this->fitAction = action;
      this->newFit = true;
      this->fitMutex.unlock();

    }

  } // end process

  /*-------------------------------------------------------------------------*/

  void send_result(const std::string& result) const {

    asio::io_service io_service;

    asio::ip::udp::socket s(
      io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

    asio::ip::udp::resolver resolver(io_service);
    asio::ip::udp::endpoint endpoint =
      *resolver.resolve({
          asio::ip::udp::v4(),
            this->settings.targetHost.c_str(),
            (std::to_string(this->settings.outputPort)).c_str()});

    s.send_to(asio::buffer(result.c_str(), result.length()), endpoint);

  }

  /*-------------------------------------------------------------------------*/

  std::string convert_to_json_string(
    const arma::vec& speakerWeights,
    const arma::vec& phonemeWeights
    ) {

    Json::Value json(Json::objectValue);
    Json::Value jsonSpeakerWeights(Json::arrayValue);
    Json::Value jsonPhonemeWeights(Json::arrayValue);

    for(const double& weight: speakerWeights) {
      jsonSpeakerWeights.append(weight);
    }

    for(const double& weight: phonemeWeights) {
      jsonPhonemeWeights.append(weight);
    }

    json["speakerWeights"] = jsonSpeakerWeights;
    json["phonemeWeights"] = jsonPhonemeWeights;
    json["timeStamp"] = this->tracker.data().currentTime;

    Json::FastWriter writer;

    return writer.write(json);

  }

  /*-------------------------------------------------------------------------*/


  // stored actions
  std::priority_queue<YAML::Node> managementActions;
  YAML::Node fitAction;
  bool newFit = false;

  Tracker& tracker;

  Settings settings;

  TrackerActionExecuter trackerActionExecuter;

  std::mutex managementMutex;
  std::mutex fitMutex;

  /*-------------------------------------------------------------------------*/

};

#endif
