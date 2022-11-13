#pragma once

#include "sybilengine/util/quad.hpp"
#include "sybilengine/util/rect.hpp"

namespace sbl {
  class View {
  public:
    View();
    View(Rectf& rect);
    View(Vec2f bl, Vec2f tr);
  private:
  };
}
