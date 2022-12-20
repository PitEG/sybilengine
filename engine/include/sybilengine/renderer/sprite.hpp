#pragma once

#include "sybilengine/util/vec.hpp"
#include "sybilengine/util/color.hpp"

namespace sbl {
  class Sprite {
  public:
    Vec2f position;
    Color color;
    Vec2f origin;
    // Vec2f size;
    // int texture_id;
  };
}
