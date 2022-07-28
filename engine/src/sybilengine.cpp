#include "sybilengine/sybilengine.hpp"

#include <SDL2/SDL.h>

namespace sbl {
  void Engine::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
  }

  void Engine::Terminate() {
    SDL_Quit();
  }
}
