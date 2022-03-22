#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

#include "sybilengine/util/time.hpp"
/*
 * currently implements GLFW!!! std::chrono would be more platform independent
 */
namespace sbl {
  /*
   * MEMBERS
   */
  double Time::m_startTime = 0;

  /*
   * GETTERS
   */
  double Time::Now(){
    return glfwGetTime() - m_startTime;
  }

  /*
   * METHODS
   */
  void Time::Reset() {
    m_startTime = glfwGetTime();
  }

  void Time::Wait(double seconds) {
    if (seconds < 0) return;
    unsigned long int microseconds = seconds * 1'000'000;
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
  }
}
