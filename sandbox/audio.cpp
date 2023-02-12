#include <sybilengine/sybilengine.hpp>
#include <imgui.h>

int main() {
  sbl::Engine::Init();

  sbl::Window window = sbl::Window("audio");
  window.SetVsync(sbl::Window::VSYNC_ON);

  sbl::ImGUI::CreateContext(window);

  // audio file
  sbl::Sound sound(sbl::FileSystem::GetExecPath() + "sound.wav");

  while(!window.IsClosed()) {
    window.Clear();
    sbl::Input input = window.PollInput();

    // input
    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      window.Close();
    }

    sbl::ImGUI::NewFrame();
    {
      ImGui::Begin("audio test");
      ImGui::Text("%s",sbl::FileSystem::GetExecPath().c_str());
      if (ImGui::Button("play sound")) {
        sbl::Mixer::Play(sound);
      }
      ImGui::End();
    }

    sbl::ImGUI::Render();
    window.SwapBuffers();
  }

  sbl::Engine::Terminate();
}

