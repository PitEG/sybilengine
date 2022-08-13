#pragma once

#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/util/vec.hpp"

namespace sbl {
  class Sprite {
  public:
    Vec2f position;
    Vec2f origin;
    Vec2f size;
  private:
    Texture* m_texture;
  };
}
