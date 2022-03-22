#include "sybilengine/renderer/texture.hpp"

#include "sybilengine/renderer/opengl/texture.hpp"

#include <stb_image.h>
#include <iostream>

#include <glad/glad.h>

namespace sbl {
  GLuint GetColorFormat(ImageFileType ft) {
    switch(ft) {
      case ImageFileType::PNG:
        return GL_RGBA;
      case ImageFileType::JPG:
        return GL_RGB;
    }

    return ImageFileType::None;
  }
    
  Texture::Texture(const std::string& filepath, const ImageFileType fileType) : filepath(filepath) {
    
    stbi_set_flip_vertically_on_load(true); //true = flip on y axis
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0); 
    if (localBuffer == NULL) {
      std::cout << "WARNING: TEXTURE " << filepath << " DIDN'T LOAD!\n";
    } 

    /*
    textureObject = new gl::Texture();
    gl::Texture& texture = *(gl::Texture*)(textureObject);
    texture.Bind();
    */
  
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
  
    //default texture settings TODO, remove this
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
    GLint colorFormat = GetColorFormat(fileType);
  
    glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, localBuffer);
    //glGenerateMipmap(GL_TEXTURE_2D);
  
    stbi_image_free(localBuffer);
  }

  Texture::Texture(unsigned int w, unsigned int h) : width(w), height(h) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    //TODO default settings, remove this later
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_wrapType = WrapType::Repeat;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    m_filterType = FilterType::Nearest;

    //TODO only supports RGBA idk if it'll be a problem
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  }
  
  Texture::~Texture() {
    if (id == 0) {
      return;
    }
    glDeleteTextures(1, &id);
  }

  unsigned int Texture::ID() const {
    return id;
  }

  //NOT ALL TYPES HAVE BEEN IMPLEMENTED
  void Texture::SetWrap(WrapType wt) {
    glBindTexture(GL_TEXTURE_2D, id);
    GLuint type;
    switch(wt) {
      case WrapType::Repeat : type = GL_REPEAT;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
  }
  //NOT ALL TYPES HAVE BEEN IMPLEMENTED
  void Texture::SetFilter(FilterType ft) {
    glBindTexture(GL_TEXTURE_2D, id);
    GLuint type;
    switch(ft) {
      case FilterType::Linear: type = GL_LINEAR;
      case FilterType::Nearest: type = GL_NEAREST;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
  }

  void Texture::GenerateMipmaps() {
    glBindTexture(GL_TEXTURE_2D, id);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  
  void Texture::Bind(unsigned int slot) const { //defualt is 0
    int current_buffer;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &current_buffer);
    if (current_buffer == id) { return; }
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
  }
  
  void Texture::Unbind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  int Texture::Width() const {
    return width;
  }

  int Texture::Height() const {
    return height;
  }

  void* Texture::GetBackendObject() {
    return textureObject;
  }

  WrapType Texture::GetWrapType() const {
    return m_wrapType; 
  }

  FilterType Texture::GetFilterType() const {
    return m_filterType; 
  }

}
