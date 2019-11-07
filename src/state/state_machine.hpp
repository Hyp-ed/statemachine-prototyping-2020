#ifndef STATE_MACHINE_MAIN_HPP_
#define STATE_MACHINE_MAIN_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "table.hpp"
#include <iostream>
#include <cstdint>

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using data::ModuleStatus;
using data::State_enum;
using data::current_state_;
// using data::tlm_command_;
// using data::command_received;
using namespace std;


namespace state_machine {
  class Main: public Thread {
    public:
      explicit Main(uint8_t id, Logger& log);
      void run() override;

      private:
        Logger& log_;
        utils::System& sys_;

      // string tlm_command_;

      // data::command_received;

      string states[State_enum::num_states] = {
        "Idle",
        "Ready",
        "Accelerating",
        "Deccelerating",
        "EmergencyBraking",
        "FailureStopped",
        "RunComplete"
      };

      string events_[num_event] = {
        "Critical_Failure",
        "Start_Calibrating",
        "Launch",
        "Max_Distance_Reached",
        "Stop",
        "Stationary",
        "Reset"
      };

      uint64_t time_start_;
      uint64_t timeout_;

      data::Data&         data_;
      data::Telemetry     telemtry_data_;
      // data::StateMachine  sm_data_;

      Table_Entry const * p_entry = table_begin();
      Table_Entry const * const p_table_end = table_end();

      bool state_found = false;
      bool event_found = false;

      int event_size = sizeof(events_)/sizeof(events_[0]);

      Event_enum event;

      string input;
      // string tlm_command_;
  };
}

} // namespace hyped::state_machine

#endif // STATE_MACHINE_MAIN_HPP_