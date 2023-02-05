#pragma once
#include "sybilengine/renderer/texture.hpp"

namespace sbl {
  class FrameBuffer {
  public:
    FrameBuffer();
    // FrameBuffer(const unsigned int width, const unsigned int height);
    ~FrameBuffer();

    void Clear(float r, float g, float b, float a);
    void AttachTexture(const Texture& texture);
    unsigned int ID() const;
    unsigned int Width() const;
    unsigned int Height() const;

  private:
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;
  };
}
