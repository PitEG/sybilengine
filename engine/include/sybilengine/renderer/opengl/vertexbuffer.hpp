#pragma once

#include <glad/glad.h>

#include "sybilengine/renderer/opengl/bufferlayout.hpp"

namespace sbl::gl {
  class VertexBuffer {
  public:
    //void* this should usually just be an array of floats but keeping it general for now
    VertexBuffer(const void* data, int size);
    VertexBuffer();
    ~VertexBuffer();
  
    void Bind() const;
    void Unbind() const;
  
    inline int Size() const { return size; }

    void SetBufferLayout(const BufferLayout& bufferLayout) const;
    void SetBufferDivisor(const unsigned int location, const unsigned int divisor) const;
    
    inline unsigned int ID() const {
      return bufferID;  
    }
  private:
    unsigned int bufferID = 0;
    int size;
  };
}
