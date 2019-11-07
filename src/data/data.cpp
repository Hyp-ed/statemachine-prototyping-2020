#include "data/data.hpp"

namespace hyped {

    // imports
    using utils::concurrent::ScopedLock;

    namespace data {
        const char* states[num_states] =  {
            "Idle",
            "Calibrating",
            "Accelerating",
            "Decelerating",
            "EmergencyBraking",
            "FailureStopped",
            "RunComplete"
        };

        Data& Data::getInstance() {
            static Data d;
            return d;
        }

        StateMachine Data::getStateMachineData() {
            ScopedLock L(&lock_state_machine_);
            return state_machine_;
        }

        void Data::setStateMachineData(const StateMachine& sm_data) {
            ScopedLock L(&lock_state_machine_);
            state_machine_ = sm_data;
        }

        Telemetry Data::getTelemetryData() {
            ScopedLock L(&lock_telemetry_);
            return telemetry_;
        }

        void Data::setTelemetryData(const Telemetry& telemetry_data) {
            ScopedLock L (&lock_telemetry_);
            telemetry_ = telemetry_data;
        }
    }

    
}