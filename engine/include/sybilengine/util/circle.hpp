#pragma once

#include "sybilengine/util/vec.hpp"
#include "sybilengine/util/math.hpp"

namespace sbl {
  template<class T> struct Circle;

  using Circlef = Circle<float>;
  using Circled = Circle<double>;

  template<class T>
  struct Circle {
    T x; // center x
    T y; // center y
    T r; // radius

    constexpr Circle();
    constexpr Circle(const T x, const T y, const T radius);
    constexpr Circle(const Vec2<T>& center, const T radius);
    constexpr Circle(const Circle<T>& other);

    constexpr Vec2<T> Center() const;
    constexpr T Area() const;
    constexpr T Circumference() const;
    constexpr void Displace(const T x, const T y);
    constexpr void Displace(const Vec2<T>& displacement);
    static constexpr bool Overlap(Circle<T>& a, Circle<T>& b);
  };

  template<class T>
  constexpr Circle<T>::Circle() 
  : x(0), y(0), r(1) {
  }

  template<class T>
  constexpr Circle<T>::Circle(const T x, const T y, const T radius) 
  : x(x), y(y), r(r) {
  }

  template<class T>
  constexpr Circle<T>::Circle(const Vec2<T>& center, const T radius) 
  : x(center.x), y(center.y), r(r) {
  }

  template<class T>
  constexpr Circle<T>::Circle(const Circle<T>& other) 
  : x(other.x), y(other.y), r(other.r) {
  }

  template<class T>
  constexpr Vec2<T> Circle<T>::Center() const {
    return Vec2<T>(x,y);
  }

  template<class T>
  constexpr T Circle<T>::Area() const {
    return Math::PI * std::pow(r,2);
  }

  template<class T>
  constexpr T Circle<T>::Circumference() const {
    return Math::TAU * r;
  }
  
  template<class T>
  constexpr void Circle<T>::Displace(const T x, const T y) {
  }

  template<class T>
  constexpr void Circle<T>::Displace(const Vec2<T>& displacement) {
  }

  template<class T>
  constexpr bool Circle<T>::Overlap(Circle<T>& a, Circle<T> &b) {
    bool overlapping = false;
    float distance = Vec2f::Distance(a.center,b.center);
    float radiusSum = a.radius + b.radius;
    if (distance <= radiusSum) { overlapping = true; }
    return overlapping;
  }
}
