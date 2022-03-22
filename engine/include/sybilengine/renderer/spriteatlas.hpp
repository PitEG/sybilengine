#pragma once

#include "sybilengine/util/rect.hpp"
#include "sybilengine/util/vector2.hpp"

#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/sprite.hpp"

#include <vector>

namespace sbl {
  class SpriteAtlas {
  public:
    //
    //make 4k sprite atlases. It will edit the sprites' texture pointers to the new texture. Doesn't free their old ones.
    static std::vector<Texture*> PackSprites(std::vector<Sprite>& sprites);
  };
}
