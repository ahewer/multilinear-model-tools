#include "settings.h"
#include "TrackerData.h"
#include "Tracker.h"
#include "model/Model.h"
#include "model/ModelReader.h"
#include "NetworkServer.h"

int main(int argc, char* argv[]) {

  Settings settings(argc, argv);

  ModelReader reader(settings.model);

  Model model = reader.get_model();

  TrackerData trackerData(model, settings);
  Tracker tracker(trackerData);

  NetworkServer server(tracker, settings);
  server.run();

  return 0;

}
