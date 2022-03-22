#pragma once

#include <glad/glad.h>

namespace sbl::gl {
  class ElementBuffer {
  public:
    //void* this should usually just be an array of floats but keeping it general for now
    ElementBuffer();
    ElementBuffer(const unsigned int* data, int count);
    ~ElementBuffer();
  
    void Bind() const;
    void Unbind() const;
    
    inline unsigned int ID() const {
      return bufferID;  
    }
  
    inline unsigned int IndexCount() const {
      return indexCount;  
    }
  private:
    unsigned int bufferID = 0;
    unsigned int indexCount;
  };
}
