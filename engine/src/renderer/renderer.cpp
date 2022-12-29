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

  struct SpriteSetup {
    unsigned int VBO, VAO, IBO;
    Shader shader = Shader(
          #include "glsl/sprite_batch_vs.glsl"
          ,
          #include "glsl/sprite_batch_fs.glsl"
    );
    SpriteSetup() {
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &IBO);
      shader.Compile();
    }
  };

  // makes a vertex array and two buffers on the fly, sort of expensive.
  void Renderer::DrawSprites(FrameBuffer& fb, const std::vector<Sprite>& sprites, const Texture& texture) {
    static std::vector<float> vertices = {
      // positions
       0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  0.5f,  // triangle 1 
      -0.5f, -0.5f, 0.5f,  0.5f, -0.5f,  0.5f,  // triangle 2
    };
    static SpriteSetup spriteSetup;
    unsigned int VBO = spriteSetup.VBO;
    unsigned int VAO = spriteSetup.VAO;

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    const std::vector<sbl::Sprite>& instances = sprites;
    unsigned int instance_buffer = spriteSetup.IBO;
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * sprites.size(), instances.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)0);
    glVertexAttribDivisor(1,1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)(sizeof(Vec2f)));
    glVertexAttribDivisor(2,1);

    // bind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // currently binding default framebuffer
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetID());
    // bind shader
    glUseProgram(spriteSetup.shader.GetID());
    glUniform1i(glGetUniformLocation(spriteSetup.shader.GetID(),"texture0"),0);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, sprites.size());
  }
}
