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

  unsigned long int f = 0;
  while(!window.IsClosed()) {
    f++;

    window.Clear();

    // sbl::ImGUI::ProcessEvents(window);
    sbl::Input input = window.PollInput();

    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      std::cout << "pressed escape" << std::endl;
      window.Close();
    }
    if (input.GetKey(sbl::KeyCode::SPACE)) {
      std::cout << "pressed space" << std::endl;
      window.Clear(0.9f,0.9f,0.9f,1);
    }

    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("stuff");
      ImGui::Text("hi there");
      ImGui::End();
    }
    bool a = true;
    ImGui::ShowDemoWindow(&a);
    sbl::ImGUI::Render();

    window.SwapBuffers();
  }
  sbl::Engine::Terminate();
}
