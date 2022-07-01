#pragma once

#include "sybilengine/util/vector2.hpp"
#include "sybilengine/util/vec.hpp"

namespace sbl {
  /**
   * @brief Generic Circle object
   * 
   */
  struct Circle {
  public:
    /**
     * @brief Radius is defined by the center (and radius)
     */
    Vec2f center;
    /**
     * @brief Radius is defined by the radius (and center)
     */
    float   radius;

    /**
     * @brief Construct a default Circle object
     * 
     * @param center center of circle
     * @param radius radius of circle
     */
    Circle(Vec2f center = Vec2f::Zero(), float radius = 1);

    Circle(const Circle& other);

    /**
     * @brief Get the Area of the circle. pi * radius ^ 2
     * 
     * @return float Area of circle.
     */
    float Area() const;
    /**
     * @brief Get circumference of the circle. 2 * pi * radius
     * 
     * @return float Circumference of the circle.
     */
    float Circumference() const;

  public:
    /**
     * @brief Check to see if two given circles overlap in space.
     * 
     * @param a Circle a
     * @param b Circle b
     * @return true If the circles overlap
     * @return false If the cirlces do not overlap
     */
    static bool Overlap(const Circle& a, const Circle& b);
  };
}
