#include "sybilengine/core/imgui.hpp"
#include "sybilengine/core/keycode.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL2/SDL.h>

namespace sbl {
  void ImGUI::CreateContext(Window& window) {
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(
        (SDL_Window*)window.m_window, 
        (SDL_GLContext*)window.m_graphicsContext);
    ImGui_ImplOpenGL3_Init("#version 150");
  }

  void ImGUI::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
  }

  void ImGUI::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGUI::ProcessEvents(Window& window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
    }
  }
}
