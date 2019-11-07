#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "utils/logger.hpp"
#include <cstdint>
#include "data/data.hpp"

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using namespace std;
using utils::System;
using data::Telemetry;
using data::StateMachine;
using data::Data;
using data::State;


namespace state_machine {
  class Main: public Thread {
    public:
      Main(uint8_t id, Logger& log);
      void run() override;

      private:
        Logger& log_;
        System& sys_;
        Telemetry telemetry_data_;
        StateMachine state_machine_data_;
        Data& data_;
        State current_state_;
  };
}

} // namespace hyped::state_machine

#endif // STATE_MACHINE_HPP_