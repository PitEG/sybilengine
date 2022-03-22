#include "sybilengine/renderer/sprite.hpp"

namespace sbl {
  Sprite::Sprite(Texture* texture, const Color color)
  : m_texture(texture), origin(Vector2::Zero()), color(color) {
    if (texture != nullptr) {
      textureCoords = Rect(
          Vector2(0, 0),
          Vector2(texture->Width(),texture->Height()));
    }
  }

  const Texture* Sprite::GetTexture() const {
    return m_texture;
  }

  float Sprite::Width() const {
    return textureCoords.Size().x;
  }

  float Sprite::Height() const {
    return textureCoords.Size().y;
  }

  Vector2 Sprite::Size() const {
    return textureCoords.Size();
  }

  void Sprite::SetTexture(Texture* texture) {
    m_texture = texture;
  }

  void Sprite::SetTextureCoords(const Rect& rect) {
    textureCoords = rect;
  }
}
