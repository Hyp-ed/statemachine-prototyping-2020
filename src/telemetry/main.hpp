#ifndef TELEMETRY_MAIN_HPP_
#define TELEMETRY_MAIN_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"

namespace hyped {

    using utils::concurrent::Thread;
    using utils::Logger;

    namespace telemetry {
    
    class Main: public Thread {
        public:
            Main(uint8_t id, Logger& log);
            void run() override;    

        private:
            friend class SendLoop;
            friend class RecvLoop;
    };

    }
}

#endif