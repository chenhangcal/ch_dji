

//////////////////
// ch   2017.8.19
//////////////////









#include "flight_control_sample.hpp"
#include "camera_gimbal_sample.hpp"
#include "mfio_sample.hpp"
#include "mission_sample.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;


int main(int argc, char** argv)
{
  // Initialize variables
  int functionTimeout = 1;

  // Setup OSDK.
  Vehicle* vehicle = setupOSDK(argc, argv);

  if (vehicle == NULL)
  {
    std::cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }
  vehicle->obtainCtrlAuthority(functionTimeout);

      monitoredTakeoff(vehicle);
      gimbalCameraControl(vehicle);
      moveByPositionOffset(vehicle, 0, 6, 6, 30);
      moveByPositionOffset(vehicle, 6, 0, -3, -30);
      moveByPositionOffset(vehicle, -6, -6, 0, 0);

 //     pwmOutputBlockingApiDemo(vehicle);
      monitoredLanding(vehicle);
      runWaypointMission(vehicle, 6, 1);

  delete (vehicle);
  return 0;
}
