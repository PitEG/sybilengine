#pragma once

#include "sybilengine/core/window.hpp"
#include "sybilengine/renderer/shader.hpp"
#include "sybilengine/renderer/framebuffer.hpp"
#include "sybilengine/renderer/batch.hpp"
#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/view.hpp"

namespace sbl {
  class Renderer {
  public:
    Renderer(Window* window);
    ~Renderer();

    void DrawToScreen();
    // void DrawSpriteBatch(FrameBuffer& fb, const View& view, const Texture& texture, const Shader& shader, const SpriteBatch& spriteBatch);
    void DrawSpriteBatch(const Shader& shader, const SpriteBatch& spriteBatch);
    void Test(const Shader& shader);
  private:
    Window* m_window;
  };
}
