#pragma once 

#include <glm/glm.hpp>
#include "sybilengine/util/vector2.hpp"
#include "sybilengine/util/rect.hpp"

#include "sybilengine/renderer/opengl/viewport.hpp"

namespace sbl {
  /**
   * @brief A 2D camera that is defined by a viewport.
   */
  class View {
  public:
    /*
     * Constructors
     */
    
    /**
     * @brief Construct a default View object. It's a viewport of (0,0) BL and (0,0) TR
     * so it shows nothing.
     */
    View();
    /**
     * @brief Construct a new View object.
     * 
     * @param rect The viewport. It is defined by a Rect, and represents pixel locations.
     */
    View(const Rect& rect);

    /*
     * Methods
     */

    /**
     * @brief Move the viewport a specified amount of pixels.
     * 
     * @param displacement A Vector2 to displace the camera by. Note that it Vector2's
     * are comprised of floats and it's possible to have subpixel locations.
     */
    void Move(const Vector2& displacement);

    /**
     * @brief Change the size of the viewport multiplicatively by factor.
     * 
     * @param factor A float to multiply the size by. Note that since it's a float,
     * the resulting veiwport could have non-integer values and represent subpixel amounts.
     */
    void Scale(const float factor); //also sets viewport accordingly

    /**
     * @brief Set the Rect object which represents the viewport.
     * 
     * @param rect The Rect to replace the current viewport.
     */
    void SetRect(const Rect& rect); //also sets viewport accordingly

    /*
     * Getters
     */

    /**
     * @brief Get the OpenGL Viewport object
     * 
     * @return const gl::Viewport& The OpenGL Viewport object reference.
     */
    const gl::Viewport& GetViewport() const;

    /**
     * @brief Get the Projection matrix of the object. 
     * 
     * @return const glm::mat4& the GLM matrix object reference.
     */
    const glm::mat4& GetProjection() const;

    /**
     * @brief Get the Rect object that represents the viewport.
     * 
     * @return const Rect& A copy of the Rect object.
     */
    Rect GetRect() const;

  private:
    Rect          m_rect;     //view dimension
    gl::Viewport  m_viewport; //should match the ortho
    glm::mat4     m_ortho;    //matrix projection of view defintion
  };
}
