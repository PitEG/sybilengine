#pragma once 

namespace sbl::gl {
  class Viewport {
  public:
    int x, y;
    int width, height;

    Viewport(int x,int y,int width,int height);
    Viewport();

    void Bind() const;
    //TODO sets the default viewport
    void Unbind();
  private:
  };
}
