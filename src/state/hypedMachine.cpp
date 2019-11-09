#include "state/hypedMachine.hpp"

namespace hyped {
namespace state_machine {

HypedMachine::HypedMachine(Logger& log)
  : log_(log),
  data_(Data::getInstance()),
  state_machine_data_(data_.getStateMachineData()),
  firstCheck_(true)
  {}

  bool checkCriticalFailure(string command){
    if(command == "Critical_failure"){
      return true;
    } else if(firstCheck_){
      return false;
    }
  }
  bool checkStopCommand(string command){
    if(command == "Stop"){
      return true;
    } else if(firstCheck_){
      return false;
    }
  }
  bool checkCalibrateCommand(string command){
    if(command == "Start_Calibrating"){
      return true;
    } else{
      return false;
    }
  }
  bool checkLaunchCommand(string command){
    if(command == "Critical_failure"){
      return true;
    } else{
      return false;
    }
  }
  bool checkMaxDistanceReached(string command){
    if(command == "Max_distance_reached"){
      return true;
    } else{
      return false;
    }
  }
  bool checkAtRest(string command){
    if(command == "Not_moving"){
      return true;
    } else{
      return false;
    }
  }

}} //hyped::state_machine
