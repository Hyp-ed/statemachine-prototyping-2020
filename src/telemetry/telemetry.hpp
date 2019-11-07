#ifndef TELEMETRY_HPP_
#define TELEMETRY_HPP_

#include "utils/concurrent/thread.hpp"
#include "utils/system.hpp"
#include "utils/logger.hpp"
#include <iostream>
#include "data/data.hpp"

namespace hyped {

using utils::concurrent::Thread;
using utils::System;
using utils::Logger;
using data::Telemetry;
using data::Data;
using namespace std;

namespace telemetry {
  class Main: public Thread {
    public:
      Main(uint8_t id, Logger& log);
      void run() override;

    private:
      Logger& log_;
      System& sys_;
      Data& data_;
      Telemetry telemetry_data_;

      string input;
  };

} //namespace telemetry
} //namespace hyped

#endif // TELEMETRY_HPP_