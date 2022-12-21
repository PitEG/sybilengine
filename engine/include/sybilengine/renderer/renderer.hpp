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
    void DrawSpriteBatch(const SpriteBatch& spriteBatch);
    void Test(const Shader& shader);
    
    template<class T>
    static void DrawBatch(
        FrameBuffer& fb,
        View& view,
        Texture& texture,
        Batch<T>& batch
        );
  private:
    Window* m_window;
  };
}
