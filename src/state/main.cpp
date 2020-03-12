#include "state/main.hpp"

namespace hyped {
namespace state_machine {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(System::getSystem()),
      data_(Data::getInstance()),
      previous_command_(""),
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
          if(checker_.checkCriticalFailure(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkCalibrateCommand(command_received_, previous_command_)) break;
          break;
        case State::kReady:
          if(checker_.checkCriticalFailure(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkLaunchCommand(command_received_, previous_command_)) break;
          break;
        case State::kAccelerating:
          if(checker_.checkCriticalFailureMoving(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkMaxDistanceReached(command_received_, previous_command_)) break;
          break;
        case State::kDeccelerating:
          if(checker_.checkCriticalFailureMoving(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkAtRest(command_received_, previous_command_)) break;
          break;
          break;
        case State::kEmergencyBraking:
          if(checker_.checkCriticalFailure(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkAtRest(command_received_, previous_command_)) break;
          break;
          break;
        case State::kRunComplete:
          if(checker_.checkCriticalFailure(command_received_, previous_command_)) break;
          if(checker_.checkStopCommand(command_received_, previous_command_)) break;
          if(checker_.checkReset(command_received_, previous_command_)) break;
          break;
        case State::kFailureStopped:
          if(checker_.checkResetAfterFailure(command_received_, previous_command_)) break;
          break;
          break;
        default:
          break;
        }
    }
}

}} // namespace hyped::state_machine
