#pragma once

#include "sybilengine/util/freelist.hpp"
#include "sybilengine/util/color.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/util/rect.hpp"

namespace sbl {
  class SpriteBatch {
  public:
    struct Settings {
      bool yOrdering = false;
    };
    Settings settings;

    SpriteBatch(const int reserveSize = 1);

    int Add(const Sprite& sprite);
    void Delete(const int id);
    void Modify(const int id, const Sprite& sprite);
    // get pointers to the data
    bool Get(const int id, 
      Vector2* origin, Vector2* position, float* rotation, Vector2* size, 
      Color* color, Vector2* textureDisplacement, Vector2* textureSize);
    Sprite& operator[](const int idx);
    const Sprite& operator[](const int idx) const;

    // specific modifications
    void ModifyOrigin(const int id, Vector2 origin);
    void ModifyPosition(const int id, Vector2 position);
    void ModifyRotation(const int id, float rotation);
    void ModifyScale(const int id, Vector2 size);
    void ModifyColor(const int id, Color color);
    void ModifyTextureCoords(const int id, Vector2 texDisp, Vector2 texSize);
    void ModifyTextureCoords(const int id, Rect texCoords);

  private:
    FreeList<u_int8_t/*dummy value*/> m_sprites;
    // just need to keep track of free spaces and disable
    // sprites when they are taken out.

    // arrays that we can just send to the renderer
    friend class Renderer;
    std::vector<float> m_origins; //vec2
    std::vector<float> m_positions; //vec2
    std::vector<float> m_rotations; //float
    std::vector<float> m_scales; //vec2
    std::vector<float> m_colors; //vec4
    std::vector<float> m_textureDisplacements; //vec2
    std::vector<float> m_textureSizes; //vec2
    std::vector<unsigned int>   m_enableds; //uint
  };
}