#pragma once 

namespace sbl {
  class Random {
  public:
    int originalSeed = 0;
    int currentSeed = 0;

    Random();
    Random(int seed);

    /**
     * @brief Returns a int between 0 and max
     * 
     * @param max max value this random int can be
     * @return int Random int between 0 and max
     */
    int RangeInt(const int max);

    /**
     * @brief Returns a float between 0 and max
     * 
     * @param max max value this float can be
     * @return float Random value between 0 and max
     */
    float RangeFloat(const float max);

  private:
  };
}