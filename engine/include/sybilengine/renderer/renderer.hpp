#pragma once

#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/renderer/lineshape.hpp"
#include "sybilengine/renderer/rectangleshape.hpp"
#include "sybilengine/renderer/view.hpp"
#include "sybilengine/renderer/blendmode.hpp"
#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/renderbatch.hpp"
#include "sybilengine/util/rect.hpp"

//opengl
#include <vector>

namespace sbl {
  /**
   * @brief A Renderer object that draws stuff to Frame Buffers / Textures.
   */
  class Renderer {
  public:

    /**
     * @brief Construct a new Renderer object. Initializes buffers. 
     */
    Renderer();
    /**
     * @brief Destroy the Renderer object
     */
    ~Renderer();

    //clears the given texture with the given color
    
    /**
     * @brief Clears the given texture with a given color
     * 
     * @param texture Texture to clear.
     * @param colorTexture Color to clear with.
     */
    void Clear(Texture& texture, const Color);

    //
    //BATCH RENDERERING
    //

    /**
     * @brief Draws a list of sprites using the same texture sheet. It draws them in order.
     * 
     * @param sprites The list of Sprite objects to draw (in order).
     * @param view The View (camera) that we draw from.
     * @param framebuffer The frame buffer we draw onto.
     * @param texture The Texture we draw the sprite from.
     * @param blendMode The BlendMode to use when drawing.
     */
    void Draw(
      std::vector<Sprite>& sprites, 
      View& view, 
      Sprite& framebuffer, 
      Texture* texture,
      const BlendMode& blendMode = BlendMode::AlphaBlending());
    //Draw a list of rectangles
    
    /**
     * @brief Draw a list of rectangles.
     * 
     * @param rects The list of Rect objects to draw (in order).
     * @param view The View (camera) to draw from.
     * @param canvas The sprite to draw onto.
     * @param blendMode The Blendmode to use when drawing.
     */
    void Draw(std::vector<RectangleShape>& rects, const View& view, Sprite& canvas, const BlendMode& bm = BlendMode::AlphaBlending());

    /**
     * @brief Draw a list of lines.
     * 
     * @param lines The list of Line objects to draw (in order).
     * @param view  The View (camera) to draw from.
     * @param framebuffer The frame buffer to draw onto.
     */
    void Draw(std::vector<LineShape>& lines, View& view, Sprite& framebuffer, const BlendMode& blendmode = BlendMode::AlphaBlending());

    // Drawing One Thing At a Time.

    /**
     * @brief Draw a Sprite stretched to the given rect of the screen.
     * 
     * @param sprite The Sprite to draw.
     * @param rect The Rect describing the section of the screen to draw on.
     */
    void DrawToScreen(Sprite& sprite, Rect& rect);

    /**
     * @brief Draw a single Sprite to a canvas.
     * 
     * @param sprite Sprite to draw.
     * @param view View (camera) to draw from.
     * @param canvas Sprite to draw onto.
     */
    void Draw(const Sprite& sprite, const View& view, Sprite& canvas);


  private:
    //default texture
    Texture*            defaultTexture;
  };
}
