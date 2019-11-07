#include "table.hpp"
// #include "data/data.hpp"

namespace hyped {

    static const Table_Entry state_event_table[] = {
        // Current State, 				Event, 				Next State
        {State_enum::kIdle,             CriticalFailure, 	State_enum::kFailureStopped},
        {State_enum::kIdle,             StartCali, 			State_enum::kReady},
        {State_enum::kReady,            CriticalFailure, 	State_enum::kFailureStopped},
        {State_enum::kReady,            Launch, 			State_enum::kAccelerating},
        {State_enum::kAccelerating,     CriticalFailure, 	State_enum::kEmergencyBraking},
        {State_enum::kAccelerating,     MaxDisMeet, 		State_enum::kDeccelerating},
        {State_enum::kDeccelerating,    CriticalFailure, 	State_enum::kEmergencyBraking},
        {State_enum::kDeccelerating, 	NotMoving, 			State_enum::kRunComplete},
        {State_enum::kRunComplete, 		CriticalFailure, 	State_enum::kFailureStopped},
        {State_enum::kRunComplete, 		Reset, 				State_enum::kIdle},
        {State_enum::kEmergencyBraking, NotMoving, 			State_enum::kFailureStopped},
        {State_enum::kFailureStopped, 	Reset, 				State_enum::kIdle}
    };

    static const unsigned int TABLE_SIZE 
        = sizeof(state_event_table)/sizeof(state_event_table[0]);

    Table_Entry const * table_begin(void) {
        return &state_event_table[0];
    };

    Table_Entry const * table_end(void) {
        return &state_event_table[TABLE_SIZE];
    }
}

