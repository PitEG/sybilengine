#pragma once 

#include <string>

#include "sybilengine/core/window.hpp"
#include "sybilengine/renderer/opengl/bufferbits.hpp"
#include "sybilengine/util/color.hpp"

namespace sbl {
  /**
   * @brief Extends the Window class to be used with drawing/rendering.
   */
  class RenderWindow : public Window {
  public:
    /**
     * @brief Construct a new Render Window object.
     * 
     * @param name Name of window.
     * @param width Width of the window.
     * @param height Height of the window.
     * @param resizable If the window can be resized.
     */
    RenderWindow(const std::string name = "Sybil Render Window",
        const unsigned int width = 1280,
        const unsigned int height = 720,
        const bool resizable = true);
    virtual ~RenderWindow();

    /**
     * @brief Set this window as the Current Context to draw to.
     */
    virtual void SetAsCurrentContext() const override;

    /**
     * @brief Clear the default window framebuffer.
     * 
     * @param bufferbits The buffers to clear.
     * @param color The Color that the color buffer will be cleared with.
     */
    virtual void Clear(BufferBits bufferbits, Color color = Color(0,0,0,0)) override;
  };
}
