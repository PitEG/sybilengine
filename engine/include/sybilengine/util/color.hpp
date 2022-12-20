#pragma once 

namespace sbl {
  /*
   * RGBA Color Struct 
   */
  
  /**
   * @brief Color struct in RGBA
   */
  struct Color {
    /**
     * @brief Red color component.
     */
    float r;
    /**
     * @brief Green color component.
     */
    float g;
    /**
     * @brief Blue color component.
     */
    float b;
    /**
     * @brief Alpha color component.
     */
    float a;

    /**
     * @brief Construct a Color object
     * 
     * @param r Red Color Component.
     * @param g Red Color Component.
     * @param b Red Color Component.
     * @param a Red Color Component.
     */
    Color(float r, float g, float b, float a) 
    : r(r), g(g), b(b), a(a) {
    }

    Color() : Color(1,1,1,1) {
    }

    /*
     * Shorthand colors
     */
    
    /**
     * @brief A White Color
     * 
     * @return A White Color object
     */
    static Color White() { return Color(1,1,1,1); }
  };
}
