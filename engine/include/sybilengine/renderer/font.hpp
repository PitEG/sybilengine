#pragma once

#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/util/vec.hpp"

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
      Vec2f size;
      Vec2f bearing;
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
