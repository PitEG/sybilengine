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

  void Renderer::DrawSpriteBatch(const Shader& shader, const SpriteBatch& spriteBatch) {
    std::vector<float> vertices = spriteBatch.vertices;
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    const std::vector<sbl::Sprite>& instances = spriteBatch.entries.GetData();
    unsigned int instance_buffer;
    glGenBuffers(1, &instance_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * instances.size(), instances.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)0);
    glVertexAttribDivisor(1,1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)(2*sizeof(float)));
    glVertexAttribDivisor(2,1);

    glUseProgram(shader.m_shaderId);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(float) * vertices.size(), spriteBatch.Size());
    // glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(float) * vertices.size(), 1);

    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&instance_buffer);
    glDeleteVertexArrays(1,&VAO);
  }
}
