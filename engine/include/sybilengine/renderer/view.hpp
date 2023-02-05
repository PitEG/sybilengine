#pragma once

#include "sybilengine/util/rect.hpp"
#include <glm/glm.hpp>

namespace sbl {
  class View {
  public:
    View();
    View(const Rectf& rect);
    View(const Vec2f bl, const Vec2f tr);

    Rectf GetRect() const;
    void Translate(const Vec2f displacement);
    glm::mat4x4 GetProjection() const;

  private:
    Rectf m_rect;
  };
}
