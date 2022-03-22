#pragma once 

namespace sbl {
  //CONSTANTS

  /**
   * @brief Math library for ease of access and utilization.
   */
  class Math {
  public:
    /**
     * @brief float precise value of pi. 
     */
    static const float PI;

    /**
     * @brief Converts degrees into radians.
     * 
     * @param d degrees.
     * @return float radian equivalent.
     */
    static float DegreeToRad(const float d);

    /**
     * @brief Converts radians into degrees.
     * 
     * @param r radians.
     * @return float degree equivalent.
     */
    static float RadToDegree(const float r);

    /**
     * @brief Clamps value inbetween min and max
     * 
     * @param value 
     * @param min 
     * @param max 
     * @return float 
     */
    static float Clamp(const float value, const float min, const float max);

    static float Abs(const float v);

    static float Sqrt(const float v);

    static float Sin(const float radians);

    static float Cos(const float radians);
  };
}
