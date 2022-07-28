#include <sybilengine/sybilengine.hpp>

#include <iostream>

#include <SDL2/SDL.h>

int main() {
  sbl::Engine::Init();
  std::cout << "hello, world!" << std::endl;
  sbl::Window window = sbl::Window("test");
  window.SetVsync(sbl::Window::VSYNC_ON);

  unsigned long int f = 0;
  while(!window.IsClosed()) {
    f++;
    sbl::Input input = window.PollInput();
    if (input.GetKey(sbl::KeyCode::ESCAPE)) {
      std::cout << "pressed escape" << std::endl;
      window.Close();
    }
    if (input.GetKey(sbl::KeyCode::SPACE)) {
      std::cout << "pressed space" << std::endl;
    }
    std::cout << "frame: " << std::to_string(f) << std::endl;

    window.SwapBuffers();
  }
  sbl::Engine::Terminate();
}
