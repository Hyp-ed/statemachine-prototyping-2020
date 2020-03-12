#ifndef HYPED_MACHINE_HPP_
#define HYPED_MACHINE_HPP_

#include "data/data.hpp"
#include "utils/logger.hpp"
#include <atomic>

namespace hyped {

using data::Data;
using utils::Logger;
using data::State;

namespace state_machine {
class HypedMachine {
 public:
  HypedMachine(Logger& log);

  bool checkCriticalFailure(string command, string previous);
  bool checkCriticalFailureMoving(string command, string previous);
  bool checkStopCommand(string command, string previous);
  bool checkStopCommandMoving(string command, string previous);
  bool checkCalibrateCommand(string command, string previous);
  bool checkLaunchCommand(string command, string previous);
  bool checkMaxDistanceReached(string command, string previous);
  bool checkAtRest(string command, string previous);
  bool checkReset(string command, string previous);
  bool checkResetAfterFailure(string command, string previous);
  
 private:
  Logger& log_;
  Data& data_;
  data::StateMachine state_machine_data_;
};

} } //namespace hyped::state_machine

#endif //HYPED_MACHINE_HPP_
