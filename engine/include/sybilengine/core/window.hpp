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
        const unsigned int height = 720,
        const bool resizable = true);
    ~Window();

    Input PollInput();
    void Close();
    bool IsClosed();
    void SetVsync(int);
    int GetVsync();
    void SwapBuffers();
    unsigned int Width() const;
    unsigned int Height() const;
    void Clear(float r = 1, float g = 1, float b = 1, float a = 1);
  private:
    void* m_window;
    void* m_graphicsContext;
    bool m_closed = false;

    friend class ImGUI;
  };
}
