#include "sybilengine/core/window.hpp"
#include "sybilengine/core/keycode.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <glad/glad.h>
#include <imgui_impl_sdl.h>
#include <cstring>

namespace sbl {
  Window::Window(
      const std::string title, 
      const unsigned int width, 
      const unsigned int height,
      const bool resizable) {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    int r = resizable ? SDL_WINDOW_RESIZABLE : 0;

    m_window = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        width, 
        height,
        SDL_WINDOW_OPENGL | r | SDL_WINDOW_SHOWN);

    // handle error here 
    if (m_window == NULL) {
    }

    // create opengl context
    m_graphicsContext = (void*)SDL_GL_CreateContext((SDL_Window*)m_window);
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    SDL_GL_MakeCurrent((SDL_Window*)m_window, (SDL_GLContext*)m_graphicsContext);
  }

  Window::~Window() {
    SDL_DestroyWindow((SDL_Window*)m_window);
    SDL_GL_DeleteContext((SDL_GLContext*)m_graphicsContext);
  }

  /**
   * I am using the SDL poll input function beceause it lets me queue up inputs that
   * happened inbetween poll calls. This way I don't just take a snapshot but actually
   * have a queue and it's neigh impossible to miss an input just cuz someone pressed
   * it quicker than I can take snapshots.
   */
  Input Window::PollInput() {
    Input input = Input();
    SDL_PumpEvents();
    SDL_Event ev;

    // take current snapshot of keyboard
    int keyboardArraySize;
    const Uint8* state = SDL_GetKeyboardState(&keyboardArraySize);
    memcpy(&input.KeyState, state, keyboardArraySize * sizeof(bool));

    // take current snapshot of mouse
    SDL_GetMouseState(&input.Mouse.x, &input.Mouse.y);

    // if there are any queued events, process them
    while (SDL_PollEvent(&ev) != 0) {
      // for imgui, this probably isn't necessary
      ImGui_ImplSDL2_ProcessEvent(&ev);

      // SDL_Log("%d", ev.type);
      if (ev.type == SDL_WINDOWEVENT) {
        switch (ev.window.event) {
          case SDL_WINDOWEVENT_CLOSE: m_closed = true; SDL_Log("pressed closed"); break;
        }
      }
      if (ev.type == SDL_KEYDOWN) {
        input.KeyState[ev.key.keysym.scancode] = true; 
      }
      if (ev.type == SDL_MOUSEBUTTONDOWN) {
        switch(ev.button.button) {
          case SDL_BUTTON_LEFT: input.Mouse.m1 = true;
          case SDL_BUTTON_RIGHT: input.Mouse.m2 = true;
          case SDL_BUTTON_MIDDLE: input.Mouse.m3 = true;
          case SDL_BUTTON_X1: input.Mouse.m4 = true;
          case SDL_BUTTON_X2: input.Mouse.m5 = true;
        }
      }
    }
    // SDL_Delay(50);
    return input;
  }

  void Window::Close() {
    m_closed = true;
  }

  bool Window::IsClosed() {
    return m_closed;
  }

  void Window::SetVsync(int setting) {
    // this should be 1, 0 or -1
    int returnCode = SDL_GL_SetSwapInterval(setting); 
    // if adaptive sync was enabled but the system doesn't support it or something
    // fall back to regular vsync.
    if (setting == Window::ADAPTIVE_SYNC_ON && returnCode == -1) {
      SDL_GL_SetSwapInterval(Window::VSYNC_ON);
    }
  }

  // 1 for vsync, 0 for no vsync, -1 for adaptive sync
  int Window::GetVsync() {
    return SDL_GL_GetSwapInterval();
  }

  void Window::SwapBuffers() {
    SDL_GL_SwapWindow((SDL_Window*)m_window);
  }

  void Window::Clear(float r, float g, float b, float a) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // bind default framebuffer
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}
