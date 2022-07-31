#pragma once 

#include <sys/types.h>
namespace sbl {

  /**
   * @brief Timer Class
   * This is a global clock that keeps track of when GLFW i
   * (or whatever window backend) initialized. Or, reset and 
   * counts from when it was reset.
   */
  class Time {
  public:
    /*
     * GETTERS
     */
    /* 
     * */

    /**
     * @brief Returns the time since m_startTime. If m_startTime = 0, 
     * it's essentially returning when GLFW was first initialized.
     * Returns the number of seconds.
     * 
     * @return A double representing the seconds passed.
     */
    static double Now();

    /*
     * Methods
     */

    /**
     * @brief Resets when we start keeping time to now
     */
    static void Reset();
    /**
     * @brief Have this thread wait for a specified amount of time.
     * 
     * @param seconds The amount of time to wait.
     */
    static void Wait(double seconds);

  private:
    static u_int64_t m_startTime;
  };
}
