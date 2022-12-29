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

  Texture(const std::string& path);
  Texture(const unsigned int w, const unsigned int h); // make an empty texture

  void GenerateMipmaps();
  ~Texture();

  unsigned int GetID() const;
  unsigned int GetWidth() const;
  unsigned int GetHeight() const;

  private:
    unsigned int m_id;
    int m_width;
    int m_height;
    Wrap m_wrap;
    Filter m_filter;
  };
}
