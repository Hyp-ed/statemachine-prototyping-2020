#include "utils/logger.hpp"
#include "utils/system.hpp"
#include "state/state_machine.hpp"
#include "telemetry/main.hpp"
#include "utils/concurrent/thread.hpp"

using hyped::utils::Logger;
using hyped::utils::System;
using hyped::utils::concurrent::Thread;

int main(int argc, char* argv[])
{
  System::parseArgs(argc, argv);
  System& sys = System::getSystem();

  Logger log_system(sys.verbose, sys.debug);
  Logger log_state(sys.verbose_state, sys.debug_state);
  Logger log_tlm(sys.verbose_tlm, sys.debug_tlm);


  log_system.INFO("MAIN", "Starting system with %d module", 1);
  log_system.DBG("MAIN", "DBG0");
  log_system.DBG1("MAIN", "DBG1");
  log_system.DBG2("MAIN", "DBG2");
  log_system.DBG3("MAIN", "DBG3");

  // Initalise the threads here
  Thread* state_machine = new hyped::state_machine::Main(1, log_state);
  // Thread* telemetry = new hyped::telemetry::Main(2, log_tlm);
  // Thread* telemetry     = new hyped::telemetry::Main(2, log_te);

  // Start the threads here
  state_machine -> start();
  // telemetry -> start();

  // Join the threads here
  state_machine -> join();
  // telemetry -> join();

  delete state_machine;
  // delete telemetry;

  return 0;
}