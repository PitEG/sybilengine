#pragma once

#include "sybilengine/util/vec.hpp"
#include "sybilengine/util/color.hpp"
#include "sybilengine/util/rect.hpp"

namespace sbl {
  class Sprite {
  public:
    Vec2f position;
    Color color;
    Vec2f origin;
    Vec2f size;
    float rotation; // in radians
    Rectui textCoord;
    unsigned int texture;
  };
}
