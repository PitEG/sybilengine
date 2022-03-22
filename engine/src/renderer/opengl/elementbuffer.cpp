#include "sybilengine/renderer/opengl/elementbuffer.hpp"

namespace sbl::gl {
  ElementBuffer::ElementBuffer() : bufferID(0){
  }
  ElementBuffer::ElementBuffer(const unsigned int* data, int count) :
  indexCount(count) {  
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
        count * sizeof(unsigned int), data, GL_STATIC_DRAW);
  }
  
  ElementBuffer::~ElementBuffer() {
    if (bufferID == 0) { //don't delete if this buffer isn't real
      return;
    }
    glDeleteBuffers(1, &bufferID); 
  }
  
  void ElementBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
  }
  
  void ElementBuffer::Unbind() const {
    int current_buffer;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &current_buffer);
    if (current_buffer == bufferID) { return; }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}
