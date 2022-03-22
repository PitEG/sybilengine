#pragma once 

#include <string> // change layer to string instead of an int.

#include "sybilengine/util/vector2.hpp"

namespace sbl {
  /**
   * @brief Positional information. Can be used as component for the ECS.
   */
  struct Transform {
  public:
    /**
     * @brief Position in world space.
     */
    Vector2 position;
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
      : position(Vector2::Zero()), rotation(0), layer(0) {}
    /**
     * @brief Construct a new Transform object
     * 
     * @param position Position.
     * @param rotation Rotation (in radians).
     * @param layer Layer number.
     */
    Transform(const Vector2 position, const float rotation, const int layer) 
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
     * @param displacement The Vector2 to displace by.
     */
    inline void Translate(const Vector2 displacement) { position = position + displacement; }
  private:
  };
}
