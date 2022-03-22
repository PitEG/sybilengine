#include "sybilengine/renderer/opengl/framebuffer.hpp" 

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace sbl::gl {
  FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &id);
  }

  FrameBuffer::~FrameBuffer() {
    if (id != 0) {
      glDeleteFramebuffers(1, &id);
    }
  }

  void FrameBuffer::Clear(float r, float g, float b, float a) {
    Bind();
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  //TODO DELETE THESE DRAW FUNCTIONS
  void FrameBuffer::Draw(VertexArray& va, ElementBuffer& eb) {
    va.Bind();
    eb.Bind();
    glDrawElements(GL_TRIANGLES, eb.IndexCount(), GL_UNSIGNED_INT, 0); 
  }

  void FrameBuffer::Draw(VertexArray& va, ElementBuffer& eb, BlendMode& bm) {
    va.Bind();
    eb.Bind();
    glEnable(GL_BLEND);
    glBlendFuncSeparate(bm.colorSrcFactor, bm.colorDstFactor, 
        bm.alphaSrcFactor, bm.alphaDstFactor);
    glBlendEquationSeparate(bm.colorEquation, bm.alphaEquation);
    glDrawElements(GL_TRIANGLES, eb.IndexCount(), GL_UNSIGNED_INT, 0); 
  }

  unsigned int FrameBuffer::ID() const {
    return id;
  }

  void FrameBuffer::Bind() {
    int current_buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &current_buffer);
    if (current_buffer == id) { return; }
    glBindFramebuffer(GL_FRAMEBUFFER, id);
  }

  void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  bool FrameBuffer::CheckStatus() {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER);
  }
  
  void FrameBuffer::BindTexture(const sbl::Texture& texture) {
    Bind();
    texture.Bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.ID(), 0);
  }

  void FrameBuffer::BindDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  /*
   * Static Methods
   */
  FrameBuffer FrameBuffer::DefaultFrameBuffer() {
    return FrameBuffer(0);
  }

  FrameBuffer::FrameBuffer(int id) 
  : id(0) {
  }

}
