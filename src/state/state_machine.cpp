#include "table.hpp"
#include "state_machine.hpp"
#include <iostream>

namespace hyped{
namespace state_machine{

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(utils::System::getSystem())
{}

void Main::run() {

    State_enum current_state_ = kIdle;
    Event_enum event;

    string input;

    string states[] = {
      "Idle",
      "Ready",
      "Accelerating",
      "Deccelerating",
      "EmergencyBraking",
      "FailureStopped",
      "RunComplete"
    };

    string events_[] = {
      "Critical_Failure",
      "Start_Calibrating",
      "Launch",
      "Max_Distance_Reached",
      "Stop",
      "Stationary",
      "Reset"
    };

    while (sys_.running_){
        
        cout << "Current state:" << states[current_state_] << endl;
        cin >> input;

        Table_Entry const * p_entry = table_begin();
        Table_Entry const * const p_table_end = table_end();
        bool state_found = false;
        bool event_found = false;
        int event_size = sizeof(events_)/sizeof(events_[0]);

        for (int e = CriticalFailure; e != Last; e++ ) {
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
                        break;
                    }
                }
                ++p_entry;
            }
        } else {
            cout << "Illegal Input!";
        }
        

        // if (event_found)
        // {
        //     // do sth
        // }
        

    }
}

}}