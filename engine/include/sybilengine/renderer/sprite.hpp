#pragma once 

#include "sybilengine/util/color.hpp"
#include "sybilengine/util/rect.hpp"
#include "sybilengine/ecs/transform.hpp"
#include "sybilengine/renderer/texture.hpp"
#include "sybilengine/renderer/blendmode.hpp"

namespace sbl {
  /**
   * @brief Sprite object used for rendering. Important to know that the Renderer
   * object may ignore some info about the Sprite. This object will store any useful
   * information that may be ignored.
   */
  class Sprite {
  public:
    /**
     * @brief The positional information of the Sprite.
     */
    Transform transform;

    /**
     * @brief Defines the center of the sprite. 
     * For example: (0,0) means that the sprite's center is right in the middle of the sprite. 
     * And (20,20) means the sprite's center is 20 pixels up and 20 pixels to the right of the
     * middle of the sprite.
     */
    Vec2f   origin;
    
    /**
     * @brief Sprite's color. Depending on the shader program, this will do something different.
     * The regalar sprite shader mixes this with the texture.
     */
    Color     color;

    /**
     * @brief The BlendMode to draw with.
     */
    BlendMode blendMode;

    /**
     * @brief The Texture coordinates that the sprite uses from the source Texture pointer.
     */
    Rect      textureCoords;

    /*
     * Constructors
     */

    /**
     * @brief Construct a default Sprite object. This sprite has no texture and initializes
     * its member variables with default values.
     */
    Sprite() : Sprite(nullptr) {}

    /**
     * @brief Construct a new Sprite object.
     * 
     * @param texture The Texture object to draw from. By default, the Sprite will just use
     * the whole Texture.
     * @param color The Color of the Sprite. By default, it is white. In the default sprite shader,
     * a White sprite will just use the Texture to determine the colors of the pixel.
     */
    Sprite(Texture* texture, const Color color = sbl::Color::White());

    /*
     * Getters
     */

    /**
     * @brief Get the Texture object
     * 
     * @return const Texture* A pointer to the Texture object. It cannot be changed for safety.
     */
    const Texture* GetTexture() const;

    /**
     * @brief Get the width the Sprite. Note the the size is a float, meaning that 
     * the sprite * can be of subpixel size and does not represent the pixel size.
     * 
     * @return float The width of the Sprite.
     */
    float Width() const;

    /**
     * @brief Get the height the Sprite. Note the the size is a float, meaning that 
     * the sprite * can be of subpixel size and does not represent the pixel size.
     * 
     * @return float The height of the Sprite.
     */
    float Height() const;

    /**
     * @brief Get the size the Sprite. Note the the size is a float, meaning that 
     * the sprite * can be of subpixel size and does not represent the pixel size.
     * 
     * @return Vec2f A Vector (x,y) where x is the width and y is the height.
     */
    Vec2f Size() const;

    /*
     * Setters
     */
    void SetTexture(Texture* texture);
    //remember, rects are defined by the BL corner and its size. not BL and TR
    void SetTextureCoords(const Rect& rect);

  private:
    /**
     * @brief The Texture object the sprite is from. The Sprite doesn't need
     * to use the whole Texture and can define what part is needed with the 
     * textureCoords member variable.
     * 
     */
    Texture*  m_texture;
  };
}
