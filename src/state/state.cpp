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

    string events[] = {
      "Critical_Failure",
      "Start_Calibrating",
      "Launch",
      "Max_Distance_Reached",
      "Stop",
      "Stationary",
      "Reset"
    };
    
    while(sys_.running_){

      cout << "Current state: " << states[current_state_] << endl;
      cin >> input;

      switch(current_state_) {
        case kIdle:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user" << endl;
          } else if(input == events[CriticalFailure]){
            current_state_= kFailureStopped;
          } else if(input == events[StartCali]){
            current_state_ = kReady;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kReady:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user" << endl;
          } else if(input == events[CriticalFailure]){
            current_state_= kFailureStopped;
          } else if(input == events[Launch]){
            current_state_ = kAccelerating;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kAccelerating:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user" << endl;
          } else if(input == events[CriticalFailure]){
            current_state_= kEmergencyBraking;
          } else if(input == events[MaxDisMeet]){
            current_state_ = kDeccelerating;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kDeccelerating:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user" << endl;
          } else if(input == events[CriticalFailure]){
            current_state_= kEmergencyBraking;
          } else if(input == events[NotMoving]){
            current_state_ = kRunComplete;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kEmergencyBraking:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user" << endl;
          } else if(input == events[NotMoving]){
            current_state_= kFailureStopped;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kFailureStopped:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user";
          } else if(input == events[Reset]){
            current_state_= kIdle;
          }
          else {
            cout << "Illegal input!\n";
          }
          break;
        case kRunComplete:
          if(input==events[Stop]){
            sys_.running_ = false;
            cout << "Stop command received from user";
          } else if(input == events[CriticalFailure]){
            current_state_= kFailureStopped;
          } else if(input == events[Reset]){
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