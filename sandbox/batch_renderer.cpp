#include "sybilengine/util/vec.hpp"
#include <sybilengine/sybilengine.hpp>
#include <iostream>

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
  window.SetVsync(sbl::Window::VSYNC_OFF);
  sbl::ImGUI::CreateContext(window);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  sbl::Renderer renderer(&window);

  sbl::Shader shader(
#include "glsl/sprite_batch_vs.glsl"
        ,
#include "glsl/sprite_batch_fs.glsl"
        );

  shader.Compile();

  std::vector<float> vertices = {
    // positions
    0.1f, -0.1f, 
    -0.1f, -0.1f, 
    0.0f,  0.1f, 
  };
  std::vector<unsigned int> sizes = {3};
  sbl::SpriteBatch batch(vertices, shader);
  batch.sizes = sizes;
  sbl::Sprite sprite1;
  sbl::Sprite sprite2;
  sprite1.position = sbl::Vec2f(0,0);
  sprite2.position = sbl::Vec2f(0.5f,0.5f);
  sprite1.color = sbl::Color(1,0,0,0);
  sprite2.color = sbl::Color(0,1,0,0);
  batch.Add(sprite1);
  batch.Add(sprite2);
  unsigned int amount = 20000;
  int half = amount/2;
  int sqrt = sbl::Math::Sqrt(amount);
  for (int i = 0; i < sqrt; i++) {
    for (int j = 0; j < sqrt; j++) {
      // float x = (float)(i*sqrt- half)*2/amount;
      // float y = (float)(j*sqrt - half)*2/amount;
      // sprite1.position = sbl::Vec2f(x,y);
      batch.Add(sprite1);
    }
  }

  // debug display stuff
  sbl::Stopwatch stopwatch = sbl::Stopwatch();
  stopwatch.Reset();
  double last_frame = stopwatch.ElapsedTime();
  double current_frame = last_frame;
  while(!window.IsClosed()) {
    double frame_time = current_frame - last_frame;
    window.Clear(0.5f,0.5f,0.5f,1);

    sbl::Input input = window.PollInput();
    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      window.Close();
    }

    renderer.DrawSpriteBatch(batch);

    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("debug");
      ImGui::Text("frame time: %lf", frame_time);
      ImGui::Text("frame rate: %lf", 1 / frame_time);
      ImGui::Text("%s", shader.GetError().c_str());
      ImGui::End();
    }
    // bool imgui_demo = true;
    // ImGui::ShowDemoWindow(&imgui_demo);
    sbl::ImGUI::Render();

    window.SwapBuffers();
    // window.Close();
    last_frame = current_frame;
    current_frame = stopwatch.ElapsedTime();
  }

  sbl::Engine::Terminate();
  return 0;
}
