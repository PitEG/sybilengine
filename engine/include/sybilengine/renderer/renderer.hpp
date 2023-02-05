#pragma once

#include "sybilengine/core/window.hpp"
#include "sybilengine/util/rect.hpp"
#include "sybilengine/renderer/shader.hpp"
#include "sybilengine/renderer/framebuffer.hpp"
#include "sybilengine/renderer/batch.hpp"
#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/renderer/view.hpp"

namespace sbl {
  class Renderer {
  public:
    Renderer(Window* window);
    ~Renderer();

    // void DrawToScreen();
    // void DrawSpriteBatch(const SpriteBatch& spriteBatch);
    void Test(const Shader& shader);
    static void DrawToScreen(const Window& window, const Rectui& winRect, const Texture& texture, const Rectf& textRect);
    static void Clear(const FrameBuffer& fb);
    static void DrawBatch(FrameBuffer& fb, const Batch& batch);
    static void DrawSprites(FrameBuffer& fb, const View& view, const std::vector<Sprite>& sprite, const Texture& texture);

  private:
    Window* m_window;
  };
}
