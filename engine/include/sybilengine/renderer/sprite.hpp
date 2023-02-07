#pragma once

#include "sybilengine/util/vec.hpp"
#include "sybilengine/util/color.hpp"
#include "sybilengine/util/rect.hpp"

namespace sbl {
  class Sprite {
  public:
    Vec2f position = Vec2f::Zero();
    Color color = Color::White();
    Vec2f origin = Vec2f::Zero();
    Vec2f size = Vec2f::Zero();
    float rotation = 0; // in radians
    Rectui textCoord = Rectui(0,0,0,0);
    unsigned int texture = 0;
  };
}
