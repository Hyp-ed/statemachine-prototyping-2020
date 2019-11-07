#ifndef TELEMETRY_MAIN_HPP_
#define TELEMETRY_MAIN_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "data/data.hpp"
#include <iostream>
#include <cstdint>

namespace hyped {

using utils::concurrent::Thread;
using utils::Logger;
using data::State_enum;
using data::current_state_;
using namespace std;

namespace telemetry{

class Main: public Thread {
    public:
        explicit Main(uint8_t id, Logger& log);
        void run() override;    

    private:
        // I duuno how it works I know no telemetry
        friend class SendLoop;
        friend class RecvLoop;

    // My stuff
    // State_enum previous_state;
    Logger& log_;
    utils::System& sys_;
    data::Data& data_;

    State_enum current_state_;
    State_enum previous_state_;

    string states[State_enum::num_states] = {
        "Idle",
        "Ready",
        "Accelerating",
        "Deccelerating",
        "EmergencyBraking",
        "FailureStopped",
        "RunComplete"
    };




};

}
}

#endif