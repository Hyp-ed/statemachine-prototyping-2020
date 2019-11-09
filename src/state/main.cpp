#include "main.hpp"

namespace hyped {
namespace state_machine {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(System::getSystem()),
      data_(Data::getInstance()),
      checker_(log)
{}

void Main::run() {
    
    while(sys_.running_){
      
      state_machine_data_ = data_.getStateMachineData();
      telemetry_data_ = data_.getTelemetryData();

      current_state_ = state_machine_data_.current_state_;
      command_received_ = telemetry_data_.command;

      switch(current_state_) {
        case State::kIdle:
          if(checker_.checkCriticalFailure(command_received_)) break;
          if(checkStopCommand(command_received_)) break;
          if(checkCalibrateCommand(command_received_)) break;
          if(first_check){
            log_.INFO("STATE", "Invalid input");
            first_check = false;
          }
          break;
        case State::kReady:
          if(checkCriticalFailure(command_received_)) break;
          if(checkStopCommand(command_received_)) break;
          if(checkLaunchCommand(command_received_)) break;
          if(first_check){
            log_.INFO("STATE", "Invalid input");
            first_check = false;
          }
          break;
        case State::kAccelerating:
          if(telemetry_data_.command=="stop"){
            state_machine_data_.current_state_= State::kEmergencyBraking;
            log_.INFO("STATE", "Changed to Emergency Braking");
          } else if(telemetry_data_.command == "Critical_failure"){
            state_machine_data_.current_state_= State::kEmergencyBraking;
            log_.INFO("STATE", "Changed to Emergency Braking");
          } else if(telemetry_data_.command == "Max_distance_reached"){
            state_machine_data_.current_state_ = State::kDeccelerating;
            log_.INFO("STATE", "Changed to Deccelerating");
          }
          else {
            // log_.INFO("STATE", "Illegal input");
          }
          break;
        case State::kDeccelerating:
          if(telemetry_data_.command=="stop"){
            state_machine_data_.current_state_= State::kEmergencyBraking;
            log_.INFO("STATE", "Changed to Emergency Braking");
          } else if(telemetry_data_.command == "Critical_failure"){
            state_machine_data_.current_state_= State::kEmergencyBraking;
            log_.INFO("STATE", "Changed to Emergency Braking");
          } else if(telemetry_data_.command == "Not_moving"){
            state_machine_data_.current_state_ = State::kRunComplete;
            log_.INFO("STATE", "Changed to Run Complete");
          }
          else {
            // log_.INFO("STATE", "Illegal input");
          }
          break;
        case State::kEmergencyBraking:
          if(telemetry_data_.command == "Not_moving"){
            state_machine_data_.current_state_= State::kFailureStopped;
            log_.INFO("STATE", "Changed to Failure Stopped");
          }
          else {
            // log_.INFO("STATE", "Illegal input");
          }
          break;
        case State::kFailureStopped:
          if(telemetry_data_.command == "Reset"){
            state_machine_data_.current_state_= State::kIdle;
            log_.INFO("STATE", "Changed to Idle");
          }
          else {
            // log_.INFO("STATE", "Illegal input");
          }
          break;
        case State::kRunComplete:
          if(telemetry_data_.command == "Critical_failure"){
            state_machine_data_.current_state_= State::kFailureStopped;
            log_.INFO("STATE", "Changed to Failure Stopped");
          } else if(telemetry_data_.command == "Reset"){
            state_machine_data_.current_state_ = State::kIdle;
            log_.INFO("STATE", "Changed to Idle");
          }
          else {
            // log_.INFO("STATE", "Illegal input");
          }
          break;
        default:
          break;
        }
    }
}

}} // namespace hyped::state_machine
