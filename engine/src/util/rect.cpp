#include "sybilengine/util/rect.hpp" 

namespace sbl {
  float Rect::Area() const {
    return (m_size.x * m_size.y);
  }

  Vec2f Rect::Size() const {
    return m_size;  
  }

  void Rect::Move(Vec2f displacement) {
    m_displacement = m_displacement + displacement;
  }

  void Rect::Scale(const float factor) {
    m_size = m_size * factor;
  }

  Vec2f Rect::TL() const {
    return Vec2f(m_displacement.x, m_displacement.y + m_size.y);
  }
  Vec2f Rect::TR() const {
    // return (m_displacement + m_size);
    return Vec2f(m_displacement.x + m_size.x, m_displacement.y + m_size.y);
  }
  Vec2f Rect::BL() const {
    return m_displacement;
  }
  Vec2f Rect::BR() const {
    return Vec2f(m_displacement.x + m_size.x, m_displacement.y);
  }

  Vec2f Rect::Center() const {
    return (m_displacement + Vec2f(m_size.x * 0.5, m_size.y * 0.5));
  }

  void Rect::SetPosition(const Vec2f& position) {
    m_displacement = position - (m_size * 0.5);
  }
}
