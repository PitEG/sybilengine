#pragma once

#include <sybilengine/util/math.hpp>

namespace sbl {
  template<class T> struct Vec2;
  // not necessary yet
  // template<class T> struct Vec3;
  // template<class T> struct Vec4;

  using Vec2f = Vec2<float>;
  using Vec2d = Vec2<double>;
  using Vec2i = Vec2<int>;
  using Vec2ui = Vec2<int>;
  using Vec2l = Vec2<long>;

  template<class T> 
  struct Vec2 {
    T x;
    T y;

    constexpr Vec2();
    constexpr Vec2(T x, T y);
    constexpr Vec2(const Vec2<T>& v);

    constexpr Vec2 operator+(const Vec2<T>& rhs) const;
    constexpr Vec2 operator-(const Vec2<T>& rhs) const;
    constexpr Vec2 operator*(const Vec2<T>& rhs) const;
    constexpr Vec2 operator/(const Vec2<T>& rhs) const;

    constexpr Vec2 operator*(const T scalar) const;
    constexpr Vec2 operator/(const T scalar) const;

    constexpr Vec2 operator-() const;
    
    constexpr Vec2& operator+=(const Vec2<T>& rhs);
    constexpr Vec2& operator-=(const Vec2<T>& rhs);
    constexpr Vec2& operator*=(const Vec2<T>& rhs);
    constexpr Vec2& operator/=(const Vec2<T>& rhs);

    constexpr bool operator==(const Vec2<T>& rhs) const;
    constexpr bool operator!=(const Vec2<T>& rhs) const;

    constexpr T Length() const; // maybe shouldn't be constexpr
    constexpr T LengthSqr() const; 
    constexpr Vec2 Normalized() const; // maybe shouldn't be constexpr
    constexpr Vec2 Abs() const;

    static constexpr T Distance(const Vec2<T>& a, const Vec2<T>& b);
    static constexpr T Dot(const Vec2<T>& a, const Vec2<T>& b);
    static constexpr Vec2 Reflect(const Vec2<T>& vector, const Vec2<T>& normal);
    static constexpr T AngleDegree(const Vec2<T>& a, const Vec2<T>& b);
    static constexpr T AngleRad(const Vec2<T>& a, const Vec2<T>& b);
    static constexpr Vec2 Lerp(const Vec2<T>& a, const Vec2<T>& b, const T t);

    static constexpr Vec2 Up();
    static constexpr Vec2 Down();
    static constexpr Vec2 Left();
    static constexpr Vec2 Right();
    static constexpr Vec2 Zero();
  };

  template<class T>
  constexpr Vec2<T>::Vec2() : x(0), y(0) {}

  template<class T>
  constexpr Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}
  
  template<class T>
  constexpr Vec2<T>::Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {}

  template<class T>
  constexpr Vec2<T> Vec2<T>::Vec2::Up() { return Vec2<T>(0,1); }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Vec2::Down() { return Vec2<T>(0,-1); }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Vec2::Left() { return Vec2<T>(-1,0); }
  
  template<class T>
  constexpr Vec2<T> Vec2<T>::Vec2::Right() { return Vec2<T>(1,0); }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Vec2::Zero() { return Vec2<T>(0,0); }

  template<class T>
  constexpr Vec2<T> Vec2<T>::operator+(const Vec2<T>& rhs) const {
    return Vec2<T>(x+rhs.x, y+rhs.y);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::operator-(const Vec2<T>& rhs) const {
    return Vec2<T>(x-rhs.x, y-rhs.y);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::operator*(const Vec2<T>& rhs) const {
    return Vec2<T>(x*rhs.x, y*rhs.y);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::operator/(const Vec2<T>& rhs) const {
    return Vec2<T>(x/rhs.x, y/rhs.y);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::operator*(const T scalar) const {
    return Vec2<T>(x*scalar, y*scalar);
  }
  
  template<class T>
  constexpr Vec2<T> Vec2<T>::operator/(const T scalar) const {
    return Vec2<T>(x/scalar, y/scalar);
  }
  
  template<class T>
  constexpr Vec2<T> Vec2<T>::operator-() const {
    return Vec2<T>(-x, -y);
  }

  template<class T>
  constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  template<class T>
  constexpr Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  template<class T>
  constexpr Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  template<class T>
  constexpr Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  template<class T>
  constexpr bool Vec2<T>::operator==(const Vec2<T>& rhs) const {
    return x==rhs.x && y==rhs.y;
  }

  template<class T>
  constexpr bool Vec2<T>::operator!=(const Vec2<T>& rhs) const {
    return x!=rhs.x && y!=rhs.y;
  }

  template<class T>
  constexpr T Vec2<T>::Length() const {
    return static_cast<T>(Math::Sqrt(static_cast<float>(x*x+y*y)));
  }

  template<class T>
  constexpr T Vec2<T>::LengthSqr() const {
    return x*x+y*y;
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Normalized() const {
    T length = Math::Sqrt(x*x+y*y);
    if (length <= 0) return Vec2<T>(0,0);
    return Vec2<T>(x/length, y/length);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Abs() const {
    return Vec2<T>(Math::Abs(x), Math::Abs(y)); // math abs works only on floats atm
  }

  template<class T>
  constexpr T Vec2<T>::Distance(const Vec2<T>& a, const Vec2<T>& b) {
    const Vec2<T> c = (a - b);
    const T x = c.x;
    const T y = c.y;
    return Math::Abs(static_cast<T>(Math::Sqrt(static_cast<float>(x*x+y*y))));
  }

  template<class T>
  constexpr T Vec2<T>::Dot(const Vec2<T>& a, const Vec2<T>& b) {
    return a.x*b.x + a.y*b.y;
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Reflect(const Vec2<T>& vector, const Vec2<T>& normal) {
    T dot = vector.x*normal.x + vector.y*normal.y;
    return Vec2<T>(
        vector.x - 2 * dot * normal.x, 
        vector.y - 2 * dot * normal.y);
  }

  template<class T>
  constexpr Vec2<T> Vec2<T>::Lerp(const Vec2<T>& a, const Vec2<T>& b, const T t) {
    return Vec2<T>(Math::Lerp(a,b,t), Math::Lerp(a,b,t));
  }
}
