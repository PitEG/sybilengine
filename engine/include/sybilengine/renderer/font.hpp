#pragma once

#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/util/vector2.hpp"

#include <string>
#include <unordered_set>

namespace sbl {
  /**
   * @brief Font defintion used for drawing.
   */
  class Font {
    /**
     * @brief Character defintion for a font.
     */
    struct Character {
      Vector2 size;
      Vector2 bearing;
      unsigned int advance;
      Sprite sprite;
    };
  private:
    /**
     * @brief Font Name.
     */
    std::string name;
    /**
     * @brief Font Texture source. 
     */
    Texture*    texture;
  };
}
