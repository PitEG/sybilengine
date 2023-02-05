#include "sybilengine/renderer/renderer.hpp"
#include "sybilengine/core/keycode.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace sbl {
  Renderer::Renderer(Window* window) {
    m_window = window;
  }

  Renderer::~Renderer() {
  }

  struct ScreenSetup {
    unsigned int VBO, VAO;
    Shader shader = Shader(
      #include "glsl/screen_vs.glsl"
      ,
      #include "glsl/screen_fs.glsl"
    );
    ScreenSetup() {
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      shader.Compile();
    }
  };

  void Renderer::DrawToScreen(const Window& window, const Rectui& winRect, const Texture& texture, const Rectf& textRect) {
    static ScreenSetup screenSetup;
    unsigned int VBO = screenSetup.VBO;
    unsigned int VAO = screenSetup.VAO;
    float vertices[] = {
       1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  // triangle 1 
      -1.0f, -1.0f, 1.0f,  1.0f, -1.0f,  1.0f,  // triangle 2
    };

    // default blend mode
    glDisable(GL_BLEND);
    // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    // glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

    // bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    // bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetID());
    // bind shader
    glUseProgram(screenSetup.shader.GetID());
    glUniform1i(glGetUniformLocation(screenSetup.shader.GetID(),"texture0"),0);
    // set viewport
    glViewport(winRect.BL().x, winRect.BL().y, winRect.TR().x, winRect.TR().y);
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
  void Renderer::DrawSprites(FrameBuffer& fb, const View& view, const std::vector<Sprite>& sprites, const Texture& texture) {
    static float vertices[] = {
       0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  0.5f,  // triangle 1 
      -0.5f, -0.5f, 0.5f,  0.5f, -0.5f,  0.5f,  // triangle 2
    };
    static SpriteSetup spriteSetup;
    unsigned int VBO = spriteSetup.VBO;
    unsigned int VAO = spriteSetup.VAO;

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    const std::vector<sbl::Sprite>& instances = sprites;
    unsigned int instance_buffer = spriteSetup.IBO;
    glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * sprites.size(), instances.data(), GL_STATIC_DRAW);
    long offset = 0;
    // position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)offset);
    glVertexAttribDivisor(1,1);
    offset += sizeof(Vec2f);
    // color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)offset);
    glVertexAttribDivisor(2,1);
    offset += sizeof(Color);
    // origin 
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)offset);
    glVertexAttribDivisor(3,1);
    offset += sizeof(Vec2f);
    // scale 
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)offset);
    glVertexAttribDivisor(4,1);
    offset += sizeof(Vec2f);
    // scale 
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)offset);
    glVertexAttribDivisor(5,1);
    offset += sizeof(float);

    // bind framebuffer
    // glBindFramebuffer(GL_FRAMEBUFFER, 0); // currently binding default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, fb.ID()); 
    glViewport(0,0,fb.Width(), fb.Height());
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetID());
    // bind shader
    glUseProgram(spriteSetup.shader.GetID());
    // set uniforms
    glm::mat4x4 projection = view.GetProjection();
    glUniformMatrix4fv(glGetUniformLocation(spriteSetup.shader.GetID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(spriteSetup.shader.GetID(),"texture0"),0);
    // draw
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, sprites.size());
  }
}
