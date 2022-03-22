#include "sybilengine/util/line.hpp"

namespace sbl {
  Line::Line() 
  : a(Vector2::Zero()), b(Vector2::Zero()) {

  }

  Line::Line(Vector2 a, Vector2 b) 
  : a(a), b(b) {
  }

  float Line::Magnitude() const {
    return (a - b).Magnitude();
  }
}
