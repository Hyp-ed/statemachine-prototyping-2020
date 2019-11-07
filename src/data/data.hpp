#ifndef DATA_DATA_HPP_
#define DATA_DATA_HPP_

#include <cstdint>
#include <array>
// #include "utils/math/vector.hpp"
#include "data/data_point.hpp"
#include "utils/concurrent/lock.hpp"

using std::array;

namespace hyped {

    // imports
    using utils::concurrent::Lock;

    namespace data
    {
        // Global Module States
        enum class ModuleStatus {
            kStart,
            kInit,
            kReady,
            kCriticalFailure
        };

        struct Module
        {
            ModuleStatus module_status = ModuleStatus::kStart;
        };


        // Telementry data
        struct Telemetry : public Module
        {
            static constexpr float run_length = 1250; //m
            bool calibrate_command =        false;
            bool launch_command =           false;
            bool reset_command =            false;
            bool service_propulsion_go =    false;
            bool emergency_stop_command =   false;
            bool normal_braking_command =   true;
        };


        // State Machine States
        enum State_enum {
            kIdle,
            kReady,
            kAccelerating,
            kDeccelerating,
            kEmergencyBraking,
            kFailureStopped,
            kRunComplete,
            num_states
        };

        extern State_enum current_state_;

        extern const char* states[num_states];

        // struct  StateMachine
        // {
        //     bool critical_failure;
        //     State_enum current_state;
        // };

        // -------------------------------------------------------------------------------------------------
        // Common Data structure/class
        // -------------------------------------------------------------------------------------------------
        /**
         * @brief      A singleton class managing the data exchange between sub-team
         * threads.
         */
        class Data {
        public:
        /**
         * @brief      Always returns a reference to the only instance of `Data`.
         */
        static Data& getInstance();

        /**
         * @brief      Retrieves data related to the state machine. Data has high priority.
         */
        // StateMachine getStateMachineData();

        /**
         * @brief      Should be called by state machine team to update data.
         */
        // void setStateMachineData(const StateMachine& sm_data);


        /**
         * @brief Get the Temperature from averaged thermistor values
         *
         * @return int temperature in degrees C
         */
        int getTemperature();

        /**
         * @brief Set the Temperature from averaged thermistor values
         *
         * @param temp - temp in degrees C
         */
        void setTemperature(const int& temp);

        /**
         * @brief      Retrieves data on whether stop/kill power commands have been issued.
         */
        Telemetry getTelemetryData();

        /**
         * @brief      Should be called to update communications data.
         */
        void setTelemetryData(const Telemetry& telemetry_data);

        private:
            // StateMachine state_machine_;
            Telemetry telemetry_;


            // locks for data substructures
            Lock lock_state_machine_;
            // Lock lock_temp_;
            Lock lock_telemetry_;
            // Lock lock_batteries_;
            // Lock lock_emergency_brakes_;

        Data() {}

        public:
        Data(const Data&) = delete;
        Data& operator=(const Data &) = delete;
        Data(Data &&) = delete;
        Data & operator=(Data &&) = delete;
        };

    } // namespace data
    
}

#endif