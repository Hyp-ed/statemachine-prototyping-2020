#include "table.hpp"

static const Table_Entry state_event_table[] = {
    // Current State, Event, Next State
    {kIdle, CriticalFailure, kFailureStopped},
    {kIdle, StartCali, kReady},
    {kReady, CriticalFailure, kFailureStopped},
    {kReady, Launch, kAccelerating},
    {kAccelerating, CriticalFailure, kEmergencyBraking},
    {kAccelerating, MaxDisMeet, kDeccelerating},
    {kDeccelerating, CriticalFailure, kEmergencyBraking},
    {kDeccelerating, NotMoving, kRunComplete},
    {kRunComplete, CriticalFailure, kFailureStopped},
    {kRunComplete, Reset, kIdle},
    {kEmergencyBraking, NotMoving, kFailureStopped},
    {kFailureStopped, Reset, kIdle}
};

static const unsigned int TABLE_SIZE 
    = sizeof(state_event_table)/sizeof(state_event_table[0]);

Table_Entry const * table_begin(void) {
    return &state_event_table[0];
};

Table_Entry const * table_end(void) {
    return &state_event_table[TABLE_SIZE];
}
