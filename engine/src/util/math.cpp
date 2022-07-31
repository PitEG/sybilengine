#include "sybilengine/util/math.hpp"

#include <cmath>

namespace sbl {
  const float Math::PI = atan(1) * 4;

  float Math::DegreeToRad(const float d) {
    static const float DEGREE_TO_RAD = Math::PI / 180.f;
    return d * DEGREE_TO_RAD;
  }

  float Math::RadToDegree(const float r) {
    static const float RAD_TO_DEGREE = Math::PI / 180.f;
    return r * RAD_TO_DEGREE;
  }

  float Math::Clamp(const float value, const float min, const float max) {
    return std::fmax(min, std::fmin(value, max));
  }

  float Math::Abs(const float value) {
    if (value > 0) {
      return value;
    }
    else {
      return -value;
    }
  }

  float Math::Sqrt(const float value) {
    return std::sqrt(value);
  }

  float Math::Sin(const float radians) {
    return std::sin(radians);
  }

  float Math::Cos(const float radians) {
    return std::cos(radians);
  }
}
