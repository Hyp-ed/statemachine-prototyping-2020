#include "main.hpp"
#include "utils/timer.hpp"
#include "utils/system.hpp"
#include "data/data.hpp"
#include <iostream>
#include <cstdint>

namespace hyped {
    using data::State_enum;
    using data::current_state_;
    // using data::tlm_command;

    namespace telemetry{
        Main::Main(uint8_t id, Logger& log)
            :   Thread {id, log},
                log_(log),
                sys_(utils::System::getSystem()),
                data_(data::Data::getInstance())
        {}

        void Main::run(){
            previous_state_ = State_enum::num_states;
            while (sys_.running_) {
                // cout << previous_state_ << current_state_<<endl;
                if (previous_state_ != current_state_) {
                    // cout << "Current state:" << states[current_state_] << endl;
                    // cout << "Test";
                    previous_state_ = current_state_;
                }
            }
        }

    };
}