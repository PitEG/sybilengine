#include "sybilengine/renderer/opengl/vertexarray.hpp" 

namespace sbl::gl {
  VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
  }
  
  VertexArray::~VertexArray() {
    //glDeleteVertexArrays(1, &id); 
  }
  
  void VertexArray::Bind() const {
    int current_buffer;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_buffer);
    if (current_buffer == id) { return; }
    glBindVertexArray(id);
  }
  
  void VertexArray::AddBuffer(
      const VertexBuffer& buffer, const BufferLayout& layout, const unsigned int startIdx) {
  
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.ID());
    vbSize += buffer.Size(); //set member variable
    const std::vector<LayoutElement>& layouts = layout.Elements();
    unsigned long offset = 0; //this might be a bad idea. might break compatibility with 32 bit systems
    unsigned int layoutIdx = 0;
    for(int i = startIdx; i < startIdx + layouts.size(); i++) {
      const LayoutElement& element = layouts[layoutIdx++];
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(
        i, 
        element.count, 
        element.type,
        element.normalized, 
        layout.Stride(), 
        (const void*)offset);
      offset += element.size * element.count;
    }
  }
  void VertexArray::SetBufferDivisor(const unsigned int location, const unsigned int divisor) const {
    glBindVertexArray(id);
    glVertexAttribDivisor(location, divisor);
  }
}
