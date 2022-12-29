#include "sybilengine/renderer/texture.hpp"

namespace sbl {
  Texture::Texture(std::string path) {
  }

  Texture::Texture(unsigned int w, unsigned int h) {
  }

  Texture::~Texture() {
  }

  unsigned int Texture::GetID() const {
    return m_id;
  }
}
