#include "main.hpp"
#include "utils/timer.hpp"
#include "utils/system.hpp"
#include <iostream>
#include <cstdint>

namespace hyped {
    using data::State_enum;
    using data::current_state_;

    namespace telemetry{
        Main::Main(uint8_t id, Logger& log)
            :   Thread {id, log},
                log_(log),
                sys_(utils::System::getSystem()),
                data_(data::Data::getInstance())
        {}

        void Main::run(){
            // State enumcurrent_state_
            // // current_state_ = State_enum::kIdle;
            cout << "tel running" << endl;
            while (sys_.running_) {
                if (previous_state_ != current_state_) {
                    cout << "Current state:" << states[current_state_] << endl;
                }
            }
        }

    };
}