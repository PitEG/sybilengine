#include "sybilengine/renderer/opengl/viewport.hpp" 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sbl::gl {
  Viewport::Viewport(int x,int y,int width,int height) 
    : x(x), y(y), width(width), height(height) {
  }

  Viewport::Viewport() : x(0), y(0), width(0), height(0) {}

  void Viewport::Bind() const {
    glViewport(x, y, width, height);
  }
  
}
