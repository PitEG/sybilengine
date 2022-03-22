#include <glad/glad.h> 
#include <GLFW/glfw3.h> 

#include "sybilengine/renderer/renderwindow.hpp"

namespace sbl {
  RenderWindow::RenderWindow(const std::string name,
      const unsigned int width,
      const unsigned int height,
      const bool resizable)
    : Window(name, width, height, resizable) {
  }

  RenderWindow::~RenderWindow() {
  }

  /*
   * Methods
   */
  void RenderWindow::Clear(BufferBits bits, Color color) {
    //TODO replace this with the framebuffer class stuff
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //bind default framebuffer
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(bits.GetBits());
  }

  void RenderWindow::SetAsCurrentContext() const {
    Window::SetAsCurrentContext();
    //gladLoadGL();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  }
} 
