#ifndef UTILS_CONCURRENT_BARRIER_HPP_
#define UTILS_CONCURRENT_BARRIER_HPP_

#include <cstdint>

#include "utils/concurrent/lock.hpp"
#include "utils/concurrent/condition_variable.hpp"

namespace hyped {
namespace utils {
namespace concurrent {

class Barrier {
 public:
  explicit Barrier(uint8_t required);
  ~Barrier();

  void wait();

 private:
  uint8_t required_;
  uint8_t calls_;

  Lock    lock_;
  ConditionVariable cv_;
};

}}}   // namespace hyped::utils::concurrent

#endif  // UTILS_CONCURRENT_BARRIER_HPP_