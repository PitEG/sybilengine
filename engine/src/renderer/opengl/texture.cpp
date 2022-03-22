#include "sybilengine/renderer/opengl/texture.hpp"

#include <stb_image.h>
#include <iostream>

#include <glad/glad.h>

namespace sbl::gl {
  Texture::Texture() {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
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

  void Texture::Bind(unsigned int slot) const {
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
}
