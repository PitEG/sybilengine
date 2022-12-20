#include "sybilengine/renderer/renderer.hpp"

#include <glad/glad.h>

namespace sbl {
  Renderer::Renderer(Window* window) {
    m_window = window;
  }

  Renderer::~Renderer() {
  }

  void Renderer::DrawToScreen() {
  }

  void Renderer::Test(const Shader& shader) {
    glUseProgram(shader.m_shaderId);
  }

  void Renderer::DrawSpriteBatch(FrameBuffer& fb, const View& view, const Texture& texture, const SpriteBatch& spriteBatch) {
    const std::vector<sbl::Sprite>& instance_data = spriteBatch.entries.GetData();

    unsigned int instance_buffer;
    glGenBuffers(1, &instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, instance_data.size() * (sizeof(sbl::Sprite)+sizeof(int)), instance_data.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,(sizeof(sbl::Sprite) + sizeof(int)),(void*)0);
    glVertexAttribDivisor(2,1);
  }
}
