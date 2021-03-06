#ifndef UTILS_CONCURRENT_THREAD_HPP_
#define UTILS_CONCURRENT_THREAD_HPP_

#include <cstdint>
#include <thread>
#include "utils/logger.hpp"

namespace hyped {
namespace utils {
namespace concurrent {


class Thread {
 public:
  explicit Thread(uint8_t id, Logger& log);
  // some constructors if you do not want to specify all the details
  explicit Thread(uint8_t id);
  explicit Thread(Logger& log);
  Thread();
  virtual ~Thread();

  /**
   * @brief      Spawn new thread and call Run() method
   */
  void start();

  /**
   * @brief      Wait until the thread terminates
   */
  void join();

  /**
   * @brief      Thread entry point
   */
  virtual void run();

  static void yield();

  uint8_t getId() { return id_; }

  static void sleep(uint32_t ms);

 private:
  uint8_t id_;
  std::thread* thread_;

 protected:
  Logger& log_;
};

class BusyThread : public Thread {
 public:
  ~BusyThread();
  void run() override;
  bool running_ = true;
};

}}}   // namespace hyped::utils::concurrent

#endif  // UTILS_CONCURRENT_THREAD_HPP_