#include <sybilengine/sybilengine.hpp>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

int main() {
  sbl::Engine::Init();
  std::cout << "hello, world!" << std::endl;
  sbl::Window window = sbl::Window("test");
  window.SetVsync(sbl::Window::VSYNC_ON);

  sbl::ImGUI::CreateContext(window);

  sbl::Stopwatch stopwatch = sbl::Stopwatch();
  stopwatch.Reset();

  // imgui stuff to display
  unsigned long int f = 0;
  double last_frame = stopwatch.ElapsedTime();
  double current_frame = last_frame;
  bool vsync_on = true;

  while(!window.IsClosed()) {
    double frame_time = current_frame - last_frame;
    f++;

    window.Clear();

    // sbl::ImGUI::ProcessEvents(window);
    sbl::Input input = window.PollInput();

    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      std::cout << "pressed escape" << std::endl;
      window.Close();
    }
    if (input.GetKey(sbl::KeyCode::SPACE)) {
      window.Clear(0.9f,0.9f,0.3f,1);
    }

    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("stuff");
      ImGui::Text("hi there");
      ImGui::Text("frame time: %lf", frame_time);
      ImGui::Text("frame rate: %lf", 1 / frame_time);
      if (vsync_on) { if (ImGui::Button("vsync off")) {
          vsync_on = !vsync_on;
          window.SetVsync(sbl::Window::VSYNC_OFF);
        }
      }
      else { if (ImGui::Button("vsync on")) {
          vsync_on = !vsync_on;
          window.SetVsync(sbl::Window::VSYNC_ON);
        }
      }
      double time_elapsed = stopwatch.ElapsedTime();
      ImGui::Text("hrs since init: %lf", time_elapsed / 3600.f);
      ImGui::Text("mins since init: %lf", time_elapsed / 60.f);
      ImGui::Text("secs since init: %lf", time_elapsed);
      ImGui::Text("millisecs since init: %lf", time_elapsed * 1000);
      ImGui::End();
    }
    bool a = true;
    ImGui::ShowDemoWindow(&a);
    sbl::ImGUI::Render();

    window.SwapBuffers();
    last_frame = current_frame;
    current_frame = stopwatch.ElapsedTime();
  }
  sbl::Engine::Terminate();
}
