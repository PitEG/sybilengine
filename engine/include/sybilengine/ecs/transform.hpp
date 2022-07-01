#pragma once 

#include <string> // change layer to string instead of an int.

#include "sybilengine/util/vec.hpp"

namespace sbl {
  /**
   * @brief Positional information. Can be used as component for the ECS.
   */
  struct Transform {
  public:
    /**
     * @brief Position in world space.
     */
    Vec2f position;
    /**
     * @brief Rotational position (in radians).
     */
    float rotation;
    /**
     * @brief Layer number of the object.
     */
    int layer;

    /**
     * @brief Construct a default Transform object. Initializes default member variables.
     */
    Transform() 
      : position(Vec2f::Zero()), rotation(0), layer(0) {}
    /**
     * @brief Construct a new Transform object
     * 
     * @param position Position.
     * @param rotation Rotation (in radians).
     * @param layer Layer number.
     */
    Transform(const Vec2f position, const float rotation, const int layer) 
      : position(position), rotation(rotation), layer(layer) {}

    /**
     * @brief Rotate a specified number of degrees.
     * 
     * @param radians The amount of radians to rotate by.
     */
    inline void Rotate(const float radians) { rotation += radians; }
    /**
     * @brief Move the position a certain amount.
     * 
     * @param displacement The Vec2f to displace by.
     */
    inline void Translate(const Vec2f displacement) { position = position + displacement; }
  private:
  };
}
