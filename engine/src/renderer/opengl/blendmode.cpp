#include "sybilengine/renderer/opengl/blendmode.hpp"

namespace sbl::gl {

  BlendMode::BlendMode(Factor src, Factor dst, Equation color, Factor aSrc, Factor aDst, Equation alpha)
  : colorSrcFactor(src), colorDstFactor(dst), colorEquation(color), 
    alphaSrcFactor(aSrc), alphaDstFactor(aDst), alphaEquation(alpha) {
  }

  BlendMode BlendMode::AlphaBlending() {
    return BlendMode(
        Factor::SrcAlpha, Factor::OneMinusSrcAlpha, Equation::Add,
        Factor::One, Factor::One, Equation::Add); 
  }

  void BlendMode::Bind() const {
    glEnable(GL_BLEND);
    glBlendFuncSeparate(colorSrcFactor, colorDstFactor, 
        alphaSrcFactor, alphaDstFactor);
    glBlendEquationSeparate(colorEquation, alphaEquation);
  }

  void BlendMode::Unbind() const {
    glDisable(GL_BLEND);
  }

}
