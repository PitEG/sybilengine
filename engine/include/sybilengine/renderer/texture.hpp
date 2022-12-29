#pragma once

#include <string>

namespace sbl {
  class Texture {
  public:
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
  Texture(unsigned int w, unsigned int h); // make an empty texture

  void GenerateMipmaps();
  ~Texture();

  unsigned int GetID() const;
  unsigned int GetWidth() const;
  unsigned int GetHeight() const;

  private:
    unsigned int m_id;
    unsigned int m_width;
    unsigned int m_height;
    Wrap m_wrap;
    Filter m_filter;
  };
}
