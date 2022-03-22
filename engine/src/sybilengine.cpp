#include "sybilengine/sybilengine.hpp" 

namespace sbl {
  void Engine::Init() {
    Window::Init();
    Time::Reset();
  }

  void Engine::Terminate() {
    Window::Terminate();
  }
}
