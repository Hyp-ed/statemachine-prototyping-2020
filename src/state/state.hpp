#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include <cstdint>
#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "utils/logger.hpp"
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

    
      enum Event_enum {
        CriticalFailure,
        StartCali,
        Launch,
        MaxDisMeet,
        Stop,
        NotMoving,
        Reset,
        num_event
      };

      State table[State::num_state][Event_enum::num_event] = {
        // State/Event, CritF,                      StaCa,            Lau,                    MaxDis,                 StopCom,                      NotMo,                    Res,
        /* kIdle */     {State::kFailureStopped,    State::kReady,    State::kGar,            State::kGar,            State::kFailureStopped,       State::kGar,              State::kGar},
        /* kReady */    {State::kFailureStopped,    State::kGar,      State::kAccelerating,   State::kGar,            State::kFailureStopped,       State::kGar,              State::kGar},
        /* kAcc */      {State::kEmergencyBraking,  State::kGar,      State::kGar,            State::kDeccelerating,  State::kEmergencyBraking,     State::kGar,              State::kGar},
        /* kDec */      {State::kEmergencyBraking,  State::kGar,      State::kGar,            State::kGar,            State::kEmergencyBraking,     State::kRunComplete,      State::kGar},
        /* kEmBra */    {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kFailureStopped,   State::kGar},
        /* kRunCom */   {State::kFailureStopped,    State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kIdle},
        /* kFailStop */ {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kIdle},
        /* Fin */       {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kGar}

      };

      private:
        Logger& log_;
        System& sys_;
        Telemetry telemetry_data_;
        StateMachine state_machine_data_;
        Data& data_;
        State current_state_;

        Event_enum current_event_;

        string t_commannd;

        bool invalid_input_;
        bool state_changed_;

        
  };
}

} // namespace hyped::state_machine

#endif // STATE_MACHINE_HPP_