#pragma once

#include "sybilengine/util/timeunit.hpp"
#include "sybilengine/util/time.hpp"

namespace sbl {
  /**
   * @brief A stopwatch object that keeps track of time passed.
   * 
   */
  class Stopwatch {
  private:
    /* measured in seconds */
    double m_startTime;

  public:
    /**
     * @brief Construct a new Stopwatch object. And starts keeping track now.
     */
    Stopwatch();

    /**
     * @brief Restart the timer to count from now.
     */
    void Reset();
    /**
     * @brief Get the amount of time in seconds since the stopwatch started.
     * 
     * @return double representing the amount of seconds since the stopwatch
     * was reset.
     */
    double ElapsedTime(); //returns in seconds
    /**
     * @brief Same as reset but allows you to specify the time scale
     * 
     * @param unit The timescale
     * @return double representing the amount of time since the stopwatch was reset.
     */
    double ElapsedTime(TimeUnit unit); //return as the specified unit
  };
}
