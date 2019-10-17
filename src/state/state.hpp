#ifndef STATE_MACHINE_MAIN_HPP_
#define STATE_MACHINE_MAIN_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include <iostream>
#include <cstdint>

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using namespace std;

namespace state_machine {
  class Main: public Thread {
    public:
      explicit Main(uint8_t id, Logger& log);
      void run() override;

      private:
        Logger& log_;
        utils::System& sys_;

        enum State {
          kIdle,
          kReady,
          kAccelerating,
          kDeccelerating,
          kEmergencyBraking,
          kFailureStopped,
          kRunComplete
        };
  };
}

} // namespace hyped::state_machine

#endif // STATE_MACHINE_MAIN_HPP_