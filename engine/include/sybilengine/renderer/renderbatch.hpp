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
      Vec2f* origin, Vec2f* position, float* rotation, Vec2f* size, 
      Color* color, Vec2f* textureDisplacement, Vec2f* textureSize);
    Sprite& operator[](const int idx);
    const Sprite& operator[](const int idx) const;

    // specific modifications
    void ModifyOrigin(const int id, Vec2f origin);
    void ModifyPosition(const int id, Vec2f position);
    void ModifyRotation(const int id, float rotation);
    void ModifyScale(const int id, Vec2f size);
    void ModifyColor(const int id, Color color);
    void ModifyTextureCoords(const int id, Vec2f texDisp, Vec2f texSize);
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
