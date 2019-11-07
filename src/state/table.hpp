#ifndef TABLE_H
#define TABLE_H

#include <cstdint>
#include "data/data.hpp"
#include "utils/system.hpp"
#include "utils/logger.hpp"


// enum State_enum {
//     kIdle,
//     kReady,
//     kAccelerating,
//     kDeccelerating,
//     kEmergencyBraking,
//     kFailureStopped,
//     kRunComplete,
//     num_states
// };


namespace hyped {

    using data::State_enum;

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

    struct Table_Entry
    {
        State_enum current_state;
        Event_enum events;
        State_enum next_state;
    };



    Table_Entry const *    table_begin(void);
    Table_Entry const *    table_end(void);
}


#endif // TABLE_H
