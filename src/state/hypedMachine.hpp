#ifndef HYPED_MACHINE_HPP_
#define HYPED_MACHINE_HPP_

#include "data/data.hpp"
#include "utils/logger.hpp"
#include <atomic>

namespace hyped {

using data::Data;
using utils::Logger;

namespace state_machine {
class HypedMachine {
 public:
  HypedMachine(Logger& log);

  bool checkCriticalFailure(string command);
  bool checkStopCommand(string command);
  bool checkCalibrateCommand(string command);
  bool checkLaunchCommand(string command);
  bool checkMaxDistanceReached(string command);
  bool checkAtRest(string command);
  
 private:
  Logger& log_;
  Data& data_;
  data::StateMachine state_machine_data_;
  atomic<bool> firstCheck_;
};

} } //namespace hyped::state_machine

#endif //HYPED_MACHINE_HPP_
