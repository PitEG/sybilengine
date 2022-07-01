#include "sybilengine/renderer/lineshape.hpp"

namespace sbl {
  LineShape::LineShape(const Line line, const Color color, const BlendMode blendmode) 
  : line(line), color(color), blendmode(blendmode) {
  }

  LineShape::LineShape(const Vec2f a, const Vec2f b, const Color color, const BlendMode blendmode) 
  : color(color), blendmode(blendmode) {
    Line l(a,b);
    this->line = l;
  }
}
