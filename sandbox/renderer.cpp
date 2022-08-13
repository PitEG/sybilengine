#include <sybilengine/sybilengine.hpp>

#include <glad/glad.h>
#include <SDL2/SDL.h>
void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam ) {
  if (type != GL_DEBUG_TYPE_ERROR) { return; } // skip non errors
  SDL_Log("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

int main() {
  sbl::Engine::Init();
  sbl::Window window = sbl::Window("test");
  window.SetVsync(sbl::Window::VSYNC_ON);
  sbl::ImGUI::CreateContext(window);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  sbl::Renderer renderer(&window);

  sbl::Shader shader(
#include "glsl/test_vs.glsl"
        ,
#include "glsl/test_fs.glsl"
        );

  shader.Compile();

  float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  while(!window.IsClosed()) {
    window.Clear(0.5f,0.5f,0.5f,1);

    renderer.Test(shader); // this just binds the shader program
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    sbl::Input input = window.PollInput();
    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      window.Close();
    }
    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("debug");
      ImGui::Text("%s", shader.GetError().c_str());
      ImGui::End();
    }
    bool imgui_demo = true;
    ImGui::ShowDemoWindow(&imgui_demo);
    sbl::ImGUI::Render();

    window.SwapBuffers();
    // window.Close();
  }

  sbl::Engine::Terminate();
  return 0;
}
