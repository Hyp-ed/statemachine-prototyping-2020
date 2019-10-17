#include "state.hpp"

namespace hyped {
namespace state_machine {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(utils::System::getSystem())
{}

void Main::run() {

    State current_state_ = kIdle;

    string input;

    string states[] = {
      "Idle",
      "Ready",
      "Accelerating",
      "Deccelerating",
      "EmergencyBraking",
      "FailureStopped",
      "RunComplete"
    };
    
    while(sys_.running_){

      cout << "Current state: " << states[current_state_] << endl;
      cin >> input;

      switch(current_state_) {
        case kIdle:
          if(input=="stop"){
          } else if(input == "Critical_failure"){
            current_state_= kFailureStopped;
          } else if(input == "Start_calibrating"){
            current_state_ = kReady;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kReady:
          if(input=="stop"){
          } else if(input == "Critical_failure"){
            current_state_= kFailureStopped;
          } else if(input == "Launch"){
            current_state_ = kAccelerating;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kAccelerating:
          if(input=="stop"){
          } else if(input == "Critical_failure"){
            current_state_= kEmergencyBraking;
          } else if(input == "Max_distance_reached"){
            current_state_ = kDeccelerating;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kDeccelerating:
          if(input=="stop"){
          } else if(input == "Critical_failure"){
            current_state_= kEmergencyBraking;
          } else if(input == "Not_moving"){
            current_state_ = kRunComplete;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kEmergencyBraking:
          if(input=="stop"){
          } else if(input == "Not_moving"){
            current_state_= kFailureStopped;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kFailureStopped:
          if(input=="stop"){
          } else if(input == "Reset"){
            current_state_= kIdle;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kRunComplete:
          if(input=="stop"){
          } else if(input == "Critical_failure"){
            current_state_= kFailureStopped;
          } else if(input == "Reset"){
            current_state_ = kIdle;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        default:
          break;
        }
    }
}
}} // namespace hyped::state_machine