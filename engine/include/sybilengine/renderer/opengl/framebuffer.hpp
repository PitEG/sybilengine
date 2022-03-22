#pragma once 

#include "sybilengine/renderer/opengl/vertexarray.hpp" 
#include "sybilengine/renderer/opengl/elementbuffer.hpp" 
#include "sybilengine/renderer/opengl/blendmode.hpp" 
#include "sybilengine/renderer/texture.hpp" 

namespace sbl::gl {
  class FrameBuffer {
  public:
    FrameBuffer();
    ~FrameBuffer();
    
    unsigned int ID() const;
    bool CheckStatus();
    void Clear(float r, float g, float b, float a); 
    void Bind();
    void Unbind(); //this essential binds the default framebuffer

    //TODO remove this and just write Draw wrappers somewhere else
    //Also, write a render state object so I don't have to keep making a new draw call
    void Draw(VertexArray& va);
    void Draw(VertexArray& va, BlendMode bm);
    void Draw(VertexArray& va, ElementBuffer& eb);
    void Draw(VertexArray& va, ElementBuffer& eb, BlendMode& bm);

    //Bind a frame buffer and texture object
    void BindTexture(const sbl::Texture& texture);

    //returns a framebuffer with id 0 (ie: the default framebuffer) 
    static FrameBuffer DefaultFrameBuffer();
  
  //static methods
  public:
    static void BindDefault();

  private:
    unsigned int id = 0;
    FrameBuffer(int id);
  };
}
