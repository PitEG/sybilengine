#include "sybilengine/renderer/opengl/vertexbuffer.hpp"

#include <glad/glad.h>

namespace sbl::gl {
  VertexBuffer::VertexBuffer(const void* data, int size) : size(size) {  
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  
  }

  VertexBuffer::VertexBuffer() {
  }
  
  VertexBuffer::~VertexBuffer() {
    /* Ideally I should be interfacing with opengl to free the buffer 
     * but it will be freed automatically once opengl terminates so this is
     * redundant for my study use case. Make sure to use this before ending
     * program;
     * */
    if (bufferID == 0) {
      return; 
    }
    glDeleteBuffers(1, &bufferID); 
  }
  
  void VertexBuffer::Bind() const {
    //this is bad
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
  }
  
  void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void VertexBuffer::SetBufferLayout(const BufferLayout& layout) const {
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    const std::vector<LayoutElement>& layouts = layout.Elements();
    unsigned long offset = 0; //this might be a bad idea. might break compatibility with 32 bit systems
    for(unsigned int i = 0; i < layouts.size(); i++) {
      const LayoutElement& element = layouts[i];
      glVertexAttribPointer(
          i, 
          element.count, 
          element.type,
          element.normalized, 
          layout.Stride(), 
          (const void*)offset);
      glEnableVertexAttribArray(i);
      offset += element.size * element.count;
    }
  }
}
