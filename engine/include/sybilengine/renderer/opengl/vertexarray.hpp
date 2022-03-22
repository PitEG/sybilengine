#pragma once 

#include <glad/glad.h> 

#include "sybilengine/renderer/opengl/vertexbuffer.hpp"
#include "sybilengine/renderer/opengl/bufferlayout.hpp"

namespace sbl::gl {
  class VertexArray {
  public:
    VertexArray();
    ~VertexArray();
  
    void Bind() const;
    void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout, const unsigned int startIdx = 0);
    void SetBufferDivisor(const unsigned int location, const unsigned int divisor) const;
  
    inline unsigned int ID() const { return id; }
    inline int VBSize() const { return vbSize; }
  
  private:
    unsigned int id = 0;
    int vbSize = 0;
  };
}
