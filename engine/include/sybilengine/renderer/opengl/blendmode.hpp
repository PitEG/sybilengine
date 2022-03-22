#pragma once 

#include <glad/glad.h>

namespace sbl::gl {
  /**
   * @brief OpenGL BlendMode Wrapper. Lookup OpenGL BlendMode documentation.
   */
  class BlendMode {
  public:
    enum Factor {
      Zero                    = GL_ZERO, 
      One                     = GL_ONE,
      SrcColor                = GL_SRC_COLOR,
      OneMinusSrcColor        = GL_ONE_MINUS_SRC_COLOR, 
      DstColor                = GL_DST_COLOR,
      OneMinusDstColor        = GL_ONE_MINUS_DST_COLOR,
      SrcAlpha                = GL_SRC_ALPHA,
      OneMinusSrcAlpha        = GL_ONE_MINUS_SRC_ALPHA,
      DstAlpha                = GL_DST_ALPHA,
      OneMinusDstAlpha        = GL_ONE_MINUS_DST_ALPHA,
      ConstantColor           = GL_CONSTANT_COLOR, 
      OneMinusConstantColor   = GL_ONE_MINUS_CONSTANT_COLOR,
      ConstantAlpha           = GL_CONSTANT_ALPHA, 
      OneMinusConstantAlpha   = GL_ONE_MINUS_CONSTANT_ALPHA
    };

    enum Equation {
      Add               = GL_FUNC_ADD,
      Subtract          = GL_FUNC_SUBTRACT,
      ReverseSubtract   = GL_FUNC_REVERSE_SUBTRACT,
      Min               = GL_MIN,
      Max               = GL_MAX
    };

  public:
    /*
     * Constructor
     */
    BlendMode() {*this = AlphaBlending(); }
    BlendMode(Factor src, Factor dst, Equation color, Factor aSrc, Factor aDst, Equation alpha);

    void Bind() const;
    void Unbind() const;

    /*
     * Common Blendmodes
     */
    static BlendMode AlphaBlending(); 

  public:
    bool      enabled = true;
    Factor    colorSrcFactor;
    Factor    colorDstFactor;
    Equation  colorEquation;
    Factor    alphaSrcFactor;
    Factor    alphaDstFactor;
    Equation  alphaEquation;
  };
}
