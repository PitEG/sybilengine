#pragma once 

#include <vector>

#include "imgui.h"
#include "sybilengine/core/window.hpp"
/*
 * Dear ImGUI Context 
 */

/*
 * TODO: Rewrite this as a IMGUI context that has a list of imgui widgets to run
 * and also look through imgui_demo to learn
 */

namespace sbl {
  /**
   * @brief ImGui Context to draw onto.
   */
  class ImGuiContext {
  public:
    /**
     * @brief Construct a new ImGui Context that attached to a given window. ImGui
     * draw calls will be drawn on this window.
     * 
     * @param window The window the ImGui context will be attached to.
     */
    ImGuiContext(Window& window);
    virtual ~ImGuiContext();

    void Terminate();

    /**
     * @brief Start an Imgui Frame.
     */
    void StartFrame();
    /**
     * @brief Draw an Imgui Frame.
     */
    void RenderFrame();
    /**
     * @brief End an Imgui Frame.
     */
    void EndFrame();

  private:
  };
}
