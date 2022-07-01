#pragma once

#include "sybilengine/util/rect.hpp"
#include "sybilengine/util/vec.hpp"
#include "sybilengine/util/color.hpp"
#include "sybilengine/ecs/transform.hpp"
#include "sybilengine/renderer/blendmode.hpp"

namespace sbl {
  /**
   * @brief Rectangle Shape Object for rendering. Not very well defined, should
   * be changed a bit later. 
   */
  class RectangleShape {
  private: 
    Transform m_transform;
  public:
    /**
     * @brief The origin of the shape to act as a rotation pivot. Defined in
     * pixels.
     */
    Vec2f   origin = Vec2f(-1,-1);
    /**
     * @brief The BlendMode to draw with.
     */
    BlendMode blendMode = BlendMode::AlphaBlending();
    /**
     * @brief The Color of the Rectangle.
     */
    Color     color = Color::White();
    /**
     * @brief The width and height dimensions of the Rectangle.
     * 
     */
    Vec2f size;

    /**
     * @brief Construct a new Rectangle Shape object with a position and size.
     * 
     * @param transform The position of the Shape.
     * @param size The size of the rectangle.
     * @param color The Color of the rectangle.
     */
    RectangleShape(const Transform& transform, const Vec2f& size, const Color& color = Color::White());
    /**
     * @brief Construct a new Rectangle Shape object with a Rect and layer.
     * 
     * @param rect Rect of the object.
     * @param layer Layer of the object.
     * @param color Color of the object.
     */
    RectangleShape(const Rect& rect, const int layer, const Color& color = Color::White());

    /**
     * @brief Set the Transform of the Rectangle.
     * 
     * @param transform The new Transform.
     */
    void SetTransform(const Transform& transform);

    /**
     * @brief Get a copy of the Transform object.
     * 
     * @return Transform This Rectangle's Transform object.
     */
    Transform& GetTransform();

    /**
     * @brief Set the new defintion of the rectangle.
     * 
     * @param rect The new rectangle definitoin.
     */
    void SetRect(const Rect& rect); 

    /**
     * @brief Set the new defintion of the rectangle and layer.
     * 
     * @param rect The new rectangle definitoin.
     * @param layer The new Layer.
     */
    void SetRect(const Rect& rect, int layer); 

    /**
     * @brief Get a copy  of the Rect defintion of this shape.
     * 
     * @return Rect The Rect.
     */
    Rect GetRect() const; 

  };
}
