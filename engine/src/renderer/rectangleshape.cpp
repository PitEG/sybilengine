#include "sybilengine/renderer/rectangleshape.hpp" 

namespace sbl {

  RectangleShape::RectangleShape(const Transform& transform, const Vec2f& size, const Color& color) 
  : m_transform(transform), size(size), color(color) {
  }

  // this should probably create a rect on the fly
  Rect RectangleShape::GetRect() const {
    Rect rect(m_transform.position,size);
    return rect;
  }

  Transform& RectangleShape::GetTransform() {
    return m_transform;
  }
}
