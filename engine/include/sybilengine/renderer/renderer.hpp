#pragma once

#include "sybilengine/core/window.hpp"
#include "sybilengine/renderer/shader.hpp"
#include "sybilengine/renderer/framebuffer.hpp"
#include "sybilengine/renderer/batch.hpp"

namespace sbl {
  class Renderer {
  public:
    Renderer(Window* window);
    ~Renderer();

    void DrawToScreen();
    void DrawSpriteBatch(FrameBuffer& fb, SpriteBatch& spriteBatch);
    void Test(const Shader& shader);
  private:
    Window* m_window;
  };
}
