#ifndef UTILS_TIMER_HPP_
#define UTILS_TIMER_HPP_

#include <stdint.h>

#include "utils/utils.hpp"

namespace hyped {
namespace utils {

class Timer {
 public:
  // static uint64_t getTimeMillis();
  static uint64_t getTimeMicros();

  Timer();

  void start();
  void stop();
  void reset();
  double getSeconds() const;
  double getMillis() const;
  uint64_t getMicros() const;

 private:
  uint64_t elapsed_;
  uint64_t start_;
  uint64_t stop_;
  static uint64_t time_start_;
  NO_COPY_ASSIGN(Timer);
};

class ScopedTimer {
 public:
  explicit ScopedTimer(Timer* t)
      : timer_(t)
  {
    timer_->start();
  }

  ~ScopedTimer()
  {
    timer_->stop();
  }

 private:
  Timer* timer_;
  NO_COPY_ASSIGN(ScopedTimer);
};

}}  // namespace hyped::utils

#endif  // UTILS_TIMER_HPP_