#ifndef TABLE_H
#define TABLE_H

enum State_enum {
    kIdle,
    kReady,
    kAccelerating,
    kDeccelerating,
    kEmergencyBraking,
    kFailureStopped,
    kRunComplete,
    kLast
};

enum Event_enum {
    CriticalFailure,
    StartCali,
    Launch,
    MaxDisMeet,
    Stop,
    NotMoving,
    Reset,
    Last
};

struct Table_Entry
{
    State_enum current_state;
    Event_enum events;
    State_enum next_state;
};



Table_Entry const *    table_begin(void);
Table_Entry const *    table_end(void);

#endif // TABLE_H
