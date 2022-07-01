#pragma once

#include "sybilengine/util/line.hpp"
#include "sybilengine/util/color.hpp"
#include "sybilengine/renderer/blendmode.hpp"

namespace sbl {
  /**
   * @brief Line object for drawing.
   */
  class LineShape {
  public:
    /**
     * @brief Line defintion.
     */
    Line line;
    /**
     * @brief Color.
     */
    Color color = Color::White();
    /**
     * @brief BlendMode to draw with.
     */
    BlendMode blendmode = BlendMode::AlphaBlending();

    /**
     * @brief Construct a new Line Shape object.
     * 
     * @param line Line
     * @param color Color of the Shape.
     * @param blendmode BlendMode of the Shape.
     */
    LineShape(const Line line, const Color color = Color::White(), const BlendMode blendmode = BlendMode::AlphaBlending());
    
    /**
     * @brief Construct a new Line Shape object
     * 
     * @param a Point a
     * @param b Point b
     * @param color Color of the Shape.
     * @param blendmode BlendMode of the Shape.
     */
    LineShape(const Vec2f a, const Vec2f b, const Color color = Color::White(), const BlendMode blendmode = BlendMode::AlphaBlending());
  };
}
