#pragma once

#include <string>

namespace sbl::gl {
  class Texture {
  public:
  
    Texture();
    ~Texture();
  
    unsigned int ID() const;
    void Bind(unsigned int pos = 0) const;
    void Unbind() const;

  private:
    unsigned int id = 0;
  };
}
