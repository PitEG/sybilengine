#pragma once 

#include "sybilengine/platform.hpp"
#include "sybilengine/renderer.hpp"
#include "sybilengine/util.hpp"
#include "sybilengine/core.hpp"
#include "sybilengine/debug.hpp"
#include "sybilengine/imgui.hpp"
#include "sybilengine/ecs.hpp"
#include "sybilengine/audio.hpp"

namespace sbl {

  /**
   * @brief Used for initializing the Engine. Should be initialized only once per program,
   * so it shouldn't be instanced more than once.
   */
  class Engine {    
  private:
  public:
    /**
     * @brief Initializes any external libraries like OpenGL and GLFW
     * 
     */
    static void Init();  
    /**
     * @brief Terminates any external libraries like OpenGL and GLFW
     * 
     */
    static void Terminate();
  };
}
