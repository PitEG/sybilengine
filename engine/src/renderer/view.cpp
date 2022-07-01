#include "sybilengine/renderer/view.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace sbl {

  View::View() {
    m_rect = Rect(Vec2f::Zero(), Vec2f::Zero());
    m_ortho = glm::mat4(1);
    m_viewport = gl::Viewport();
  }

  View::View(const Rect& rect) {
    SetRect(rect);
  }

  /*
   * Methods
   */
  void View::Move(const Vec2f& displacement) {
    m_rect.Move(displacement);
    SetRect(m_rect);
  }
  
  void View::Scale(const float factor) {
    m_rect.Scale(factor);
    SetRect(m_rect);
  }

  void View::SetRect(const Rect& rect) {
    m_rect = rect;
    //set viewport
    m_viewport = gl::Viewport(0, 0, (int)rect.Size().x, (int)rect.Size().y);
    //set projection
    Vec2f bl = rect.BL();
    Vec2f tr = rect.TR();
    m_ortho = glm::ortho(bl.x, tr.x, bl.y, tr.y, -1.0f, 1.0f);
  }

  

  /*
   * Getters
   */
  const gl::Viewport& View::GetViewport() const {
    return m_viewport;
  }
  const glm::mat4& View::GetProjection() const {
    return m_ortho;
  }
  Rect View::GetRect() const {
    return m_rect;
  }
} 
