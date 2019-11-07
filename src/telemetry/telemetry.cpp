#include "telemetry.hpp"

namespace hyped {
namespace telemetry {

Main::Main(uint8_t id, Logger& log)
    : Thread(id, log),
      log_(log),
      sys_(System::getSystem()),
      data_(Data::getInstance())
{}

void Main::run() {
  while(sys_.running_){

    // get telemetry data
    telemetry_data_ = data_.getTelemetryData();
    
    // get input from terminal
    cin >> input;

    // set telemetry data
    telemetry_data_.command = input;
    data_.setTelemetryData(telemetry_data_);
    log_.INFO("Telemetry", "Command received");
  }
}

}} // namespace hyped::telemetry