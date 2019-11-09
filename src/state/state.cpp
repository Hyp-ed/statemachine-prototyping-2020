#include <iostream>
#include "state.hpp"

namespace hyped {
  // using state_table::table;
namespace state_machine {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(System::getSystem()),
      data_(Data::getInstance())
{}
void Main::run() {
    
    state_machine_data_ = data_.getStateMachineData();
    current_state_ = state_machine_data_.current_state_;
    if (current_state_ == State::kIdle) {
      log_.INFO("STATE", "Idle");
    }

    while(sys_.running_){

      state_machine_data_ = data_.getStateMachineData();
      telemetry_data_ = data_.getTelemetryData();

      current_state_ = state_machine_data_.current_state_;

      invalid_input_ = false;

      state_changed_ = false;

      if (telemetry_data_.command_sent == true) {
        log_.INFO("STATE","Command received from Telemetry");
        
        // Get telemetry command
        t_commannd = telemetry_data_.command;
        // Reset telemerty command
        telemetry_data_.command = "";
        telemetry_data_.command_sent = false;
        data_.setTelemetryData(telemetry_data_);

        // Start of Event Collector
        if (t_commannd == "stop")												current_event_ =  Event_enum::Stop;
        else if (t_commannd == "Critical_Failure") 			current_event_ =  Event_enum::CriticalFailure;
        else if (t_commannd == "Start_Calibrating") 		current_event_ =  Event_enum::StartCali;
        else if (t_commannd == "Launch") 								current_event_ =  Event_enum::Launch;
        else if (t_commannd == "Max_Distance_Reached")	current_event_ =	Event_enum::MaxDisMeet;
        else if (t_commannd == "Not_Moving") 						current_event_ =  Event_enum::NotMoving;
        else if (t_commannd == "Reset") 								current_event_ =  Event_enum::Reset;
        else if (t_commannd != "")											invalid_input_ =  true;
        // End of Event Collector

        // There is no mean to do anything but shouting to the user :(
        if (invalid_input_){
          log_.INFO("STATE", "Invalid input!");
        } else {
          if (table[current_state_][current_event_] != State::kGar) {
            state_machine_data_.current_state_ = table[current_state_][current_event_];
          }
          if (current_state_ != state_machine_data_.current_state_){
            state_changed_ = true;
            current_state_ = state_machine_data_.current_state_;
            data_.setStateMachineData(state_machine_data_);
          }
        }

        if (state_changed_) {
          switch(current_state_) {
            case State::kIdle:
              log_.INFO("STATE", "Switch to Idle");
              break;
            case State::kReady:
              log_.INFO("STATE", "Switch to Calibrating");
              break;
            case State::kAccelerating:
              log_.INFO("STATE", "Switch to Accelerarting");
              break;
            case State::kDeccelerating:
              log_.INFO("STATE", "Switch to Decelerating");
              break;
            case State::kRunComplete:
              log_.INFO("STATE", "Switch to Run Completed");
              break;
            case State::kFinished:
              log_.INFO("STATE", "Switch to Finished");
              break;
            case State::kEmergencyBraking:
              log_.INFO("STATE", "Switch to Emergency Braking");
              break;
            case State::kFailureStopped:
              log_.INFO("STATE", "Switch to Failure Stopped");
              break;
            default:
              log_.INFO("STATE", "State remains");
              break;
          }
        } else {
          log_.INFO("STATE", "State remains");
        }
      }
    }
}
}} // namespace hyped::state_machine