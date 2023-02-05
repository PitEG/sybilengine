#include "sybilengine/renderer/framebuffer.hpp"

#include <glad/glad.h>

namespace sbl {
  FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &m_id);
  }

  FrameBuffer::FrameBuffer(const unsigned int width, const unsigned int height)
  : m_width(width), m_height(height) {
    glGenFramebuffers(1, &m_id);
  }

  FrameBuffer::~FrameBuffer() {
    if (m_id != 0) {
      glDeleteFramebuffers(1, &m_id);
    }
  }
  
  void FrameBuffer::Clear(float r, float g, float b, float a) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void FrameBuffer::AttachTexture(const Texture& texture) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetID());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetID(), 0);
  }
  
  unsigned int FrameBuffer::ID() const {
    return m_id;
  }

  unsigned int FrameBuffer::Width() const {
    return m_width;
  }

  unsigned int FrameBuffer::Height() const {
    return m_height;
  }
}
