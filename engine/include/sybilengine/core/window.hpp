#pragma once

#include "sybilengine/core/input.hpp"

#include <string>

namespace sbl {
  class Window {
  public:
    static const int VSYNC_ON = 1;
    static const int VSYNC_OFF = 0;
    static const int ADAPTIVE_SYNC_ON = -1;

    Window(
        const std::string title = "sybil", 
        const unsigned int width = 1280, 
        const unsigned int height = 720);
    ~Window();

    Input PollInput();
    void Close();
    bool IsClosed();
    void SetVsync(int);
    void SwapBuffers();
  private:
    void* m_window;
    void* m_graphicsContext;
    bool m_closed;
  };
}
