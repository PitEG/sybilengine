#pragma once

#include <string>

namespace sbl {
  class Texture {
    enum Wrap {
      Repeat,
      MirroredRepeat,
      ClampEdge,
      ClampBorder
    };

    enum Filter {
      Nearest,
      Linear,
      NearMipmapNear,
      LinearMipmapNear,
      NearMipmapLinear,
      LinearMipmapLinear
    };

  Texture(std::string path);
  Texture(unsigned int w, unsigned int h);

  void GenerateMipmaps();
  ~Texture();

  private:
    void* m_texture;
    Wrap m_wrap;
    Filter m_filter;
  };
}
