#include "sybilengine/sybilengine.hpp"

#include <SDL2/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace sbl {
  void Engine::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
  }

  void Engine::Terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
  }
}
