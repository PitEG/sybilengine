#include "sybilengine/renderer/texture.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace sbl {
  Texture::Texture(const std::string& filepath) {
    stbi_set_flip_vertically_on_load(true); //true = flip on y axis
    int channels;
    unsigned char* localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &channels, 0); 
    if (localBuffer == NULL) {
      // std::cout << "WARNING: TEXTURE " << filepath << " DIDN'T LOAD!\n";
    } 
  
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
  
    //default texture settings TODO, remove this
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
    GLint colorFormat = GL_RGBA;
    if (channels == 3) {
      colorFormat = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, m_width, m_height, 0, colorFormat, GL_UNSIGNED_BYTE, localBuffer);
    //glGenerateMipmap(GL_TEXTURE_2D);
  
    stbi_image_free(localBuffer);
  }

  Texture::Texture(const unsigned int w, const unsigned int h) : m_width(w), m_height(h) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    //TODO default settings, remove this later
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_wrap = Wrap::Repeat;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    m_filter = Filter::Nearest;

    //only supports RGBA idk if it'll be a problem
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  }

  Texture::~Texture() {
    if (m_id == 0) {
      return;
    }
    glDeleteTextures(1, &m_id);
  }

  unsigned int Texture::GetID() const {
    return m_id;
  }
}
