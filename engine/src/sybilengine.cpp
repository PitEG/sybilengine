#include "sybilengine/sybilengine.hpp"

#include <SDL2/SDL.h>

namespace sbl {
  void Engine::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
  }

  void Engine::Terminate() {
    SDL_Quit();
  }
}
