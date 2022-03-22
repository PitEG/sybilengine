#include "sybilengine/imgui/imguicontext.hpp"

#include "imgui_impl_opengl3.cpp"
#include "imgui_impl_glfw.cpp"

/* 
 * IMGUI IMPLEMENTED WITH THE PROVIDED IMPLEMENTATIONS FOR GLAD AND GLFW 
 */

namespace sbl {
  /*
   * CONSTRUCTORS
   */
  ImGuiContext::ImGuiContext(Window& window) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    GLFWwindow* windowp = (GLFWwindow*)window.m_window; //ImGuiContext IS A FRIEND CLASS RN AND ACCESS A PRIVATE MEMBER WINDOW
    const char* glsl_version = "#version 150";

    ImGui_ImplGlfw_InitForOpenGL(windowp, true); 
    ImGui_ImplOpenGL3_Init(glsl_version); //currently segfaults the program
  }

  ImGuiContext::~ImGuiContext() {
    //ImGuiContext::Terminate(); //TODO make terminate private and implment here instead. working in main still so :P
  }


  /*
   * METHODS
   */
  void ImGuiContext::Terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void ImGuiContext::StartFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void ImGuiContext::RenderFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiContext::EndFrame() {
  }
}
