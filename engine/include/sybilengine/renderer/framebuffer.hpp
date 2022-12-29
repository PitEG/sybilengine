#pragma once
#include "sybilengine/renderer/texture.hpp"

namespace sbl {
  class FrameBuffer {
  public:
    FrameBuffer();
    ~FrameBuffer();

    void Clear(float r, float g, float b, float a);
    void AttachTexture(const Texture& texture);
  private:
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;
  };
}
