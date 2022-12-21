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

  // makes a vertex array and two buffers on the fly, sort of expensive.
  void Renderer::DrawSpriteBatch(const SpriteBatch& batch) {
    glDisable(GL_DEPTH_TEST);
    std::vector<float> vertices = {
      // positions
       0.5f, -0.5f, 
      -0.5f, -0.5f, 
       0.0f,  0.5f, 
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    const std::vector<sbl::Sprite>& instances = batch.entries.GetData();
    unsigned int instance_buffer;
    glGenBuffers(1, &instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * batch.Size(), instances.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)0);
    glVertexAttribDivisor(1,1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)(sizeof(Vec2f)));
    glVertexAttribDivisor(2,1);
    // glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Sprite) * batch.Size(), batch.entries.GetData().data());

    glUseProgram(batch.shader.GetShaderID());
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, batch.Size());

    // glUseProgram(batch.shader.m_shaderId);
    // glBindVertexArray(batch.m_vao);
    // glDrawArraysInstanced(GL_TRIANGLES, 0, 3, batch.Size());

    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&instance_buffer);
    glDeleteVertexArrays(1,&VAO);
  }
}
