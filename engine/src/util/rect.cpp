#include "sybilengine/util/rect.hpp" 

namespace sbl {
  float Rect::Area() const {
    return (m_size.x * m_size.y);
  }

  Vector2 Rect::Size() const {
    return m_size;  
  }

  void Rect::Move(Vector2 displacement) {
    m_displacement = m_displacement + displacement;
  }

  void Rect::Scale(const float factor) {
    m_size = m_size * factor;
  }

  Vector2 Rect::TL() const {
    return Vector2(m_displacement.x, m_displacement.y + m_size.y);
  }
  Vector2 Rect::TR() const {
    // return (m_displacement + m_size);
    return Vector2(m_displacement.x + m_size.x, m_displacement.y + m_size.y);
  }
  Vector2 Rect::BL() const {
    return m_displacement;
  }
  Vector2 Rect::BR() const {
    return Vector2(m_displacement.x + m_size.x, m_displacement.y);
  }

  Vector2 Rect::Center() const {
    return (m_displacement + Vector2(m_size.x * 0.5, m_size.y * 0.5));
  }

  void Rect::SetPosition(const Vector2& position) {
    m_displacement = position - (m_size * 0.5);
  }
}
