#pragma once

#include "sybilengine/util/vec.hpp"

namespace sbl {
  /**
   * @brief Generic Line object. Made up of a couple 2D vector points.
   */
  struct Line {
    /**
     * @brief Point a.
     */
    Vec2f a;
    /**
     * @brief Point b.
     */
    Vec2f b;

    /**
     * @brief Construct a new Line object
     * 
     * @param a Point a. 
     * @param b Point b.
     */
    Line(Vec2f a, Vec2f b);
    /**
     * @brief Construct a default Line object. Both point a and b are zero vectors.
     */
    Line();

    /**
     * @brief Get the distance between the points
     * 
     * @return float value of the distance
     */
    float Magnitude() const;
  };
}
