#pragma once 
//opengl
#include "sybilengine/renderer/opengl/texture.hpp"

#include <string>

namespace sbl {
  enum ImageFileType {
    None = -1, PNG = 0, JPG = 1
  };

  enum WrapType {
    Repeat,
    MirroredRepeat,
    ClampEdge,
    ClampBorder
  };

  enum FilterType {
    Nearest,
    Linear,
    NearMipmapNear,
    LinearMipmapNear,
    NearMipmapLinear,
    LinearMipmapLinear
  };

  class Texture {
  public:
  
    Texture(const std::string& filepath, const ImageFileType fileType);
    Texture(unsigned int w, unsigned int h); //empty texture
    ~Texture();
  
    unsigned int ID() const;
    void Bind(unsigned int = 0) const;
    void Unbind() const;

    void SetWrap(WrapType wt);
    void SetFilter(FilterType ft);
    void GenerateMipmaps();

    WrapType GetWrapType() const;
    FilterType GetFilterType() const;
    ImageFileType GetFileType() const;
  
    int Width() const;
    int Height() const;
    int BPP() const;

    void* GetBackendObject();
  
  private:
    unsigned int id = 0;
    void* textureObject = nullptr;
    std::string filepath;
    unsigned char* localBuffer; //really only used in constructor. Is pretty much wasted space.
    int width, height, nrChannels = 0;

    WrapType      m_wrapType;
    FilterType    m_filterType;
    ImageFileType m_imageFileType;
  };
}