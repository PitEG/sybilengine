#include "sybilengine/renderer/renderbatch.hpp"

namespace sbl {
  // SPRITE BATCH

  SpriteBatch::SpriteBatch(const int reserveSize) {
    m_origins.reserve(reserveSize);
    m_positions.reserve(reserveSize);
    m_rotations.reserve(reserveSize);
    m_scales.reserve(reserveSize);
    m_colors.reserve(reserveSize);
    m_textureDisplacements.reserve(reserveSize);
    m_textureSizes.reserve(reserveSize);
  }

  int SpriteBatch::Add(const Sprite& sprite) {
    int id = m_sprites.Add(0);
    if (id < m_enableds.size()) { // replace if id is not new
      int id2 = id * 2;
      int id4 = id * 4;
      m_origins[id2] = sprite.origin.x;
      m_origins[id2 +1] = sprite.origin.y;
      m_positions[id2] = sprite.transform.position.x;
      m_positions[id2 + 1] = sprite.transform.position.x;
      m_rotations[id] = sprite.transform.rotation;
      m_scales[id2] = sprite.Size().x;
      m_scales[id2 + 1] = sprite.Size().y;
      m_colors[id4] = sprite.color.r;
      m_colors[id4 + 1] = sprite.color.g;
      m_colors[id4 + 2] = sprite.color.b;
      m_colors[id4 + 3] = sprite.color.a;
      if(sprite.GetTexture() == nullptr) { 
      const Texture& texture = *(sprite.GetTexture());
        m_textureDisplacements[id2]     = 
          sprite.textureCoords.BL().x / texture.Width();
        m_textureDisplacements[id2 + 1] = 
          sprite.textureCoords.BL().y / texture.Height();
        m_textureSizes[id2]     = 
          sprite.textureCoords.Size().x / texture.Width();
        m_textureSizes[id2 + 1] = 
          sprite.textureCoords.Size().y / texture.Height();
      }
    }
    else { //if id is new (and thus goes beyond the lists' sizes, pushback)
    }

    return id;
  }
  void SpriteBatch::Delete(const int id) {
    m_sprites.Delete(id);
  }
  void SpriteBatch::Modify(const int id, const Sprite& sprite) {
  }
}
