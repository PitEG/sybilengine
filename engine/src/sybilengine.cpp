#include "sybilengine/sybilengine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace sbl {
  void Engine::Init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_SENSOR | SDL_INIT_GAMECONTROLLER);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096);
  }

  void Engine::Terminate() {
    Mix_Quit();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
  }
}
