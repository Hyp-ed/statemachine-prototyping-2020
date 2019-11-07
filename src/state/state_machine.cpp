#include "table.hpp"
#include "state_machine.hpp"
#include "utils/timer.hpp"
#include "utils/system.hpp"
#include <iostream>
#include <cstdint>

namespace hyped{
    using data::State_enum;
    using data::current_state_;
namespace state_machine{

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(utils::System::getSystem()),
      data_(data::Data::getInstance())
{}

void Main::run() {

    State_enum current_state_ = State_enum::kIdle;
    // State_enum current_state_ = State_enum::kIdle;
    
    while (sys_.running_){
    
        cout << "Current state:" << states[current_state_] << endl;
        // tlm_command_ = data::tlm_command_;
        cin >> input;

        p_entry = table_begin();
        state_found = false;
        event_found = false;

        for (int e = CriticalFailure; e != num_event; e++ ) {
            if (input == events_[e]){
                event_found = true;
                event = static_cast<Event_enum>(e);
            }
        }

        if (event_found) {
            while (p_entry != p_table_end) {
                if (p_entry -> current_state == current_state_) {
                    if (p_entry -> events == event) {
                        current_state_ = p_entry -> next_state;
                        log_.INFO("STATE", "Stage Changed");
                        break;
                    }
                }
                ++p_entry;
            }
            if (p_entry == p_table_end) {
                cout << "Illegal Input!" << endl;
            }
        } else {
            cout << "Illegal Input!" << endl;
        }
    }
}

}}