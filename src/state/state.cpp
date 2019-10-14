#include <iostream>

using namespace std;

enum State {
    kIdle,
    kReady,
    kAccelerating,
    kDeccelerating,
    kEmergencyBraking,
    kFailureStopped,
    kRunComplete
};

int main() {

    State current_state_ = kIdle;

    bool system_running_ = true;

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
    
    while(system_running_){

      cout << "Current state: " << states[current_state_] << endl;
      cin >> input;

      switch(current_state_) {
        case kIdle:
          if(input=="stop"){
            system_running_ = false;
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
            system_running_ = false;
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
            system_running_ = false;
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
            system_running_ = false;
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
            system_running_ = false;
          } else if(input == "Not_moving"){
            current_state_= kFailureStopped;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kFailureStopped:
          if(input=="stop"){
            system_running_ = false;
          } else if(input == "Reset"){
            current_state_= kIdle;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kRunComplete:
          if(input=="stop"){
            system_running_ = false;
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
    return 0;
}