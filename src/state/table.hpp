// #ifndef TABLE_HPP_
// #define TABLE_HPP_

// #include <cstdint>
// #include "data/data.hpp"


// namespace hyped {

//   using data::State;

//   namespace state_table {
//     enum Event_enum {
//     CriticalFailure,
//     StartCali,
//     Launch,
//     MaxDisMeet,
//     Stop,
//     NotMoving,
//     Reset,
//     num_event
//   };

//   State table[State::num_state][Event_enum::num_event] = {
//     // State/Event, CritF,                      StaCa,            Lau,                    MaxDis,                 StopCom,                      NotMo,                    Res,
//     /* kIdle */     {State::kFailureStopped,    State::kReady,    State::kGar,            State::kGar,            State::kFailureStopped,       State::kGar,              State::kGar},
//     /* kReady */    {State::kFailureStopped,    State::kGar,      State::kAccelerating,   State::kGar,            State::kFailureStopped,       State::kGar,              State::kGar},
//     /* kAcc */      {State::kEmergencyBraking,  State::kGar,      State::kGar,            State::kDeccelerating,  State::kEmergencyBraking,     State::kGar,              State::kGar},
//     /* kDec */      {State::kEmergencyBraking,  State::kGar,      State::kGar,            State::kGar,            State::kEmergencyBraking,     State::kRunComplete,      State::kGar},
//     /* kEmBra */    {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kFailureStopped,   State::kGar},
//     /* kRunCom */   {State::kFailureStopped,    State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kIdle},
//     /* kFailStop */ {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kIdle},
//     /* Fin */       {State::kGar,               State::kGar,      State::kGar,            State::kGar,            State::kGar,                  State::kGar,              State::kGar}

//   };
//   }
// }


// #endif