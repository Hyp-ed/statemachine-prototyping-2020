#include "state/hypedMachine.hpp"

namespace hyped {
namespace state_machine {

HypedMachine::HypedMachine(Logger& log)
  : log_(log),
  data_(Data::getInstance()),
  state_machine_data_(data_.getStateMachineData())
{}

  bool HypedMachine::checkCriticalFailure(string command, string previous){
    if(previous != command){
      if(command == "Critical_Failure"){
        state_machine_data_.current_state_= State::kFailureStopped;
        data_.setStateMachineData(state_machine_data_);

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkCriticalFailureMoving(string command, string previous){
    if(previous != command){
      if(command == "Critical_Failure"){
        state_machine_data_.current_state_= State::kEmergencyBraking;
        data_.setStateMachineData(state_machine_data_);

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkStopCommand(string command, string previous){
    if(previous != command){
      if(command == "Stop"){
        state_machine_data_.current_state_= State::kFailureStopped;
        data_.setStateMachineData(state_machine_data_);

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkStopCommandMoving(string command, string previous){
    if(previous != command){
      if(command == "Stop"){
        state_machine_data_.current_state_= State::kEmergencyBraking;
        data_.setStateMachineData(state_machine_data_);

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkCalibrateCommand(string command, string previous){
    if(previous != command){
      if(command == "Start_Calibrating"){
        state_machine_data_.current_state_= State::kReady;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");
        
        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkLaunchCommand(string command, string previous){
    if(previous != command){
      if(command == "Launch"){
        state_machine_data_.current_state_= State::kAccelerating;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkMaxDistanceReached(string command, string previous){
    if(previous != command){
      if(command == "Max_Distance_Reached"){
        state_machine_data_.current_state_= State::kDeccelerating;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkAtRest(string command, string previous){
    if(previous != command){
      if(command == "Not_Moving"){
        state_machine_data_.current_state_= State::kRunComplete;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkReset(string command, string previous){
    if(previous != command){
      if(command == "Reset"){
        state_machine_data_.current_state_= State::kIdle;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");

        return true;
      }
    }
    return false;
  }
  bool HypedMachine::checkResetAfterFailure(string command, string previous){
    if(previous != command){
      if(command == "Reset"){
        state_machine_data_.current_state_= State::kIdle;
        data_.setStateMachineData(state_machine_data_);

        return true;
      } else {
        log_.INFO("STATE", "Invalid input");

        return true;
      }
    }
    return false;
  }

}} //hyped::state_machine
