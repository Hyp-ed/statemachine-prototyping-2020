#ifndef DATA_HPP_
#define DATA_HPP_

#include <cstdint>
#include "utils/concurrent/lock.hpp"

namespace hyped {

using namespace std;
using utils::concurrent::Lock;
using utils::concurrent::ScopedLock;

namespace data {

struct Module {};

struct Telemetry : public Module {
  string command = "";
  bool command_sent = false;
};

enum State {
  kIdle,
  kReady,
  kAccelerating,
  kDeccelerating,
  kEmergencyBraking,
  kRunComplete,
  kFailureStopped,
  kFinished,
  num_state,
  kGar // Garbage State
};

struct StateMachine : public Module {
  State current_state_ = State::kIdle;
};

class Data {

  public:

    /**
     * @brief      Always returns a reference to the only instance of `Data`.
     */
    static Data& getInstance();

    /**
     * @brief      Retrieves data related to the state machine.
     */
    StateMachine getStateMachineData();

    /**
     * @brief      Should be called by state machine team to update data.
     */
    void setStateMachineData(const StateMachine& sm_data);

      /**
     * @brief      Retrieves telemetry data.
     */
    Telemetry getTelemetryData();

    /**
     * @brief      Should be called to update telemetry data.
     */
    void setTelemetryData(const Telemetry& telemetry_data);

  private:

    StateMachine state_machine_;
    Telemetry telemetry_;

    Lock lock_state_machine_;
    Lock lock_telemetry_;
};

}
}

#endif //DATA_HPP_