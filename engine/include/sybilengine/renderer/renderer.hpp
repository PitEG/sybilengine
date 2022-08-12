#pragma once

#include "sybilengine/core/window.hpp"
#include "sybilengine/renderer/shader.hpp"

namespace sbl {
  class Renderer {
  public:
    Renderer(Window* window);
    ~Renderer();

    void DrawSprite();
    void DrawToScreen();
    void Test(const Shader& shader);
  private:
    Window* m_window;
  };
}
