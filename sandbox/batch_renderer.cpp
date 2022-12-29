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

  sbl::FrameBuffer fb;
  sbl::Texture text(2,2);
  sbl::Texture sybilText(sbl::FileSystem::GetExecPath() + "sybil.png");

  fb.AttachTexture(text);
  fb.Clear(1,1,1,1);

  std::vector<sbl::Sprite> sprites;
  sbl::Sprite sprite1;
  sbl::Sprite sprite2;
  sprite1.position = sbl::Vec2f(0,0);
  sprite2.position = sbl::Vec2f(0.5f,0.5f);
  sprite1.color = sbl::Color(1,0,0,0);
  sprite2.color = sbl::Color(0,1,0,0);
  sprites.push_back(sprite1);
  sprites.push_back(sprite2);
  unsigned int amount = 1;
  int half = amount/2;
  int sqrt = sbl::Math::Sqrt(amount);
  for (int i = 0; i < sqrt; i++) {
    for (int j = 0; j < sqrt; j++) {
      // float x = (float)(i*sqrt- half)*20/amount;
      // float y = (float)(j*sqrt - half)*20/amount;
      // sprite1.position = sbl::Vec2f(x,y);
      // sprite1.color = sbl::Color(x,y,x,1);
      sprites.push_back(sprite1);
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

    renderer.DrawToScreen(window,sbl::Rectui(0,0,0,0),text,sbl::Rectf(0,0,0,0));
    renderer.DrawSprites(fb,sprites, text);

    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("debug");
      ImGui::Text("frame time: %lf", frame_time);
      ImGui::Text("frame rate: %lf", 1 / frame_time);
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
