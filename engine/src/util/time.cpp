#include <chrono>
#include <sys/types.h>
#include <thread>

#include <SDL2/SDL.h>

#include "sybilengine/util/time.hpp"
/*
 * currently implements GLFW!!! std::chrono would be more platform independent
 */
namespace sbl {
  /*
   * MEMBERS
   */
  u_int64_t Time::m_startTime = SDL_GetPerformanceCounter();

  /*
   * GETTERS
   */
  double Time::Now(){
    return (SDL_GetPerformanceCounter() - m_startTime) / (double) SDL_GetPerformanceFrequency();
  }

  /*
   * METHODS
   */
  void Time::Reset() {
    m_startTime = SDL_GetPerformanceCounter();
  }

  void Time::Wait(double seconds) {
    if (seconds < 0) return;
    unsigned long int microseconds = seconds * 1'000'000;
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
  }
}
