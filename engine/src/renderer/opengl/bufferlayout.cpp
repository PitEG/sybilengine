#include "sybilengine/renderer/opengl/bufferlayout.hpp"

#include <glad/glad.h>

namespace sbl::gl {
  /* maybe fix later
  template<typename T>
  void BufferLayout::Push(unsigned int count, bool normalized) {
    elements.push_back({sizeof(T), count, normalized});
  }
  */
  
  BufferLayout::BufferLayout() {
  }
  
  BufferLayout::~BufferLayout() {
  }
  
  
  void BufferLayout::PushFloat(unsigned int count, bool normalized) {
    elements.push_back({count, sizeof(float), GL_FLOAT, (unsigned char)normalized});
    stride += count * sizeof(float);
  }
  
  void BufferLayout::PushUnsignedInt(unsigned int count, bool normalized) {
    elements.push_back({count, sizeof(unsigned int), GL_UNSIGNED_INT, (unsigned char)normalized});
    stride += count * sizeof(float);
  }

}
