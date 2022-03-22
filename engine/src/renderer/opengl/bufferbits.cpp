#include <glad/glad.h>

#include "sybilengine/renderer/opengl/bufferbits.hpp" 

namespace sbl {
  void BufferBits::AddBit(BufferBit bit) {
    switch(bit) {
      case BufferBit::ColorBit : 
        m_bitmask = m_bitmask | GL_COLOR_BUFFER_BIT; break;
      case BufferBit::DepthBit : 
        m_bitmask = m_bitmask | GL_DEPTH_BUFFER_BIT; break;
      case BufferBit::StencilBit : 
        m_bitmask = m_bitmask | GL_STENCIL_BUFFER_BIT; break;
      default: break;
    }
  }
}
