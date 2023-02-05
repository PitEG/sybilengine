#include "sybilengine/renderer/view.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace sbl {
  View::View() {
  }

  View::View(const Rectf& rect) 
  : m_rect(rect) {
  }

  View::View(const Vec2f bl, const Vec2f tr) 
  : m_rect(Rectf(bl,tr)){
  }

  void View::Translate(const Vec2f displacement) {
    m_rect.Move(displacement.x, displacement.y);
  }

  Rectf View::GetRect() const {
    return m_rect;
  }

  glm::mat4x4 View::GetProjection() const {
    // return glm::ortho(bl.x, tr.x, bl.y, tr.y, -1.0f, 1.0f);
    return glm::ortho(m_rect.l, m_rect.r, m_rect.b, m_rect.t, -1.0f, 1.0f);
  }
}
