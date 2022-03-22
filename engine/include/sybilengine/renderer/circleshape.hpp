#pragma once

#include "sybilengine/ecs/transform.hpp"
#include "sybilengine/renderer/blendmode.hpp"
#include "sybilengine/util/vector2.hpp"
#include "sybilengine/util/circle.hpp"
#include "sybilengine/util/color.hpp"

namespace sbl {
  /**
   * @brief Circle object for drawing.
   */
  class CircleShape {
  public:
    /**
     * @brief BlendMode to draw with.
     */
    BlendMode blendMode = BlendMode::AlphaBlending();
    /**
     * @brief Color.
     */
    Color     color = Color::White();

    /**
     * @brief Construct a new Circle Shape object defined by position and radius.
     * 
     * @param transform Transform position of the circle.
     * @param radius Radius of the circle.
     */
    CircleShape(const Transform& transform, const float radius);
    /**
     * @brief Construct a new Circle Shape object defined by a circle and a layer.
     * 
     * @param circle The Circle.
     * @param layer The layer the circle shape should be in.
     */
    CircleShape(const Circle& circle, int layer);

    /**
     * @brief Set the radius of the circle.
     * 
     * @param r New radius.
     */
    void SetRadius(float r);

    /**
     * @brief Redefine shape with a new circle.
     * 
     * @param circle The circle.
     */
    void SetCircle(const Circle& circle);
    /**
     * @brief Redefine the position.
     * 
     * @param transform The new Transform position.
     */
    void SetTransform(const Transform& transform);

    /**
     * @brief Get the Circle object of the shape.
     * 
     * @return Circle The Circle.
     */
    Circle GetCircle() const;
    /**
     * @brief Get the Transform object of the shape.
     * 
     * @return Transform The Transform.
     */
    Transform GetTransform() const;

  private:
    Transform transform;
    Circle circle;
  };
}

