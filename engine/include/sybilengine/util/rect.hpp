#pragma once 

#include <sybilengine/util/vec.hpp>

namespace sbl {
  template<class T> struct Rect;

  using Rectf = Rect<float>;
  using Rectd = Rect<double>;
  using Rectui = Rect<unsigned int>;

  /**
   * very much like the rect struct except it explicitly stores
   * information for every corner. The use case would be for any
   * instance when we don't need to move a rectangle but need to
   * query corners often.
   */
  template<class T>
  struct Rect {
    T t; // top
    T b; // bottom
    T l; // left
    T r; // right

    Rect();
    Rect(T t, T b, T l, T r);
    Rect(const Vec2<T>& bl, const Vec2<T>& tr);

    void Move(T x, T y);
    void Move(Vec2<T>& displacement);
    constexpr Vec2<T> BL() const;
    constexpr Vec2<T> BR() const;
    constexpr Vec2<T> TL() const;
    constexpr Vec2<T> TR() const;
  };

  template<class T>
  Rect<T>::Rect() 
  : t(0), b(0), l(0), r(0) {
  }

  template<class T>
  Rect<T>::Rect(T t, T b, T l, T r) 
  : t(t), b(b), l(l), r(r) {
  }

  template<class T>
  void Rect<T>::Move(T x, T y) {
    t += y;
    b += y;
    l += x;
    r += x;
  }

  template<class T>
  void Rect<T>::Move(Vec2<T>& displacement) {
    Move(displacement.x, displacement.y);
  }

  template<class T>
  constexpr Vec2<T> Rect<T>::BL() const {
    return Vec2<T>(l,b);
  }

  template<class T>
  constexpr Vec2<T> Rect<T>::BR() const {
    return Vec2<T>(r,b);
  }

  template<class T>
  constexpr Vec2<T> Rect<T>::TL() const {
    return Vec2<T>(l,t);
  }

  template<class T>
  constexpr Vec2<T> Rect<T>::TR() const {
    return Vec2<T>(r,t);
  }
}
