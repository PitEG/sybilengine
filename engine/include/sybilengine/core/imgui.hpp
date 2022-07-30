#pragma once

#include "sybilengine/core/window.hpp"

namespace sbl {
  class ImGUI {
  public:
    static void CreateContext(Window& window);
    // static void Init();
    static void NewFrame();
    static void Render();
    static void ProcessEvents(Window& window);
  };
}
