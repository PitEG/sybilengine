#include "sybilengine/util/line.hpp"

namespace sbl {
  Line::Line() 
  : a(Vec2f::Zero()), b(Vec2f::Zero()) {

  }

  Line::Line(Vec2f a, Vec2f b) 
  : a(a), b(b) {
  }

  float Line::Magnitude() const {
    return (a - b).Length();
  }
}
