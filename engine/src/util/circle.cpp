#include "sybilengine/util/circle.hpp"
#include "sybilengine/util/math.hpp"

#include <cmath>

namespace sbl {
  Circle::Circle(Vector2 center, float radius) 
  : center(center), radius(radius) { 
  }

  //pi * r ^ 2
  float Circle::Area() const {
    return (Math::PI * pow(radius, 2));
  }

  //2 * pi * r
  float Circle::Circumference() const {
    return (2 * Math::PI * radius);
  }

  bool Circle::Overlap(const Circle& a, const Circle& b) {
    bool overlapping = false;
    float distance = Vector2::Distance(a.center,b.center);
    float radiusSum = a.radius + b.radius;
    if (distance > radiusSum) { overlapping = false; }
    else if (distance <= radiusSum) { overlapping = true; }
    return overlapping;
  }

}
