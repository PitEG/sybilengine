#include "sybilengine/util/vector2.hpp"
#include "sybilengine/util/math.hpp"

#include <cmath>

namespace sbl {

  Vector2::Vector2() : x(0), y(0) {}

  Vector2::Vector2(const float x, const float y) 
  : x(x), y(y) {
  }

  Vector2::Vector2(const float radians) 
  : x(Math::Cos(radians)), y(Math::Sin(radians)) {
  }

  //Instance Methods
  float Vector2::Magnitude() const {
    return std::sqrt(std::pow(x,2) + std::pow(y,2));
  }
  Vector2 Vector2::Normalize() const {
    return (Vector2(x,y))/(this->Magnitude());   
  }
  Vector2 Vector2::Absolute() const {
    return Vector2(std::abs(x), std::abs(y));
  }
  Vector2 Vector2::Normal() const {
    return Vector2(-y, x);
  }

  //Static Methods
  float Vector2::Distance(const Vector2 a, const Vector2 b) {
    return std::abs((a - b).Magnitude());
  }
  Vector2 Vector2::Reflect(const Vector2 vector, const Vector2 normal) {
    return normal * ((Vector2::Dot(vector, normal)) / (Vector2::Dot(normal, normal)) * 2) - vector;
  }
  float Vector2::Dot(const Vector2 a, const Vector2 b) {
    return (a.x * b.x) + (a.y * b.y);
  }

  float Vector2::AngleDegree(const Vector2 a, const Vector2 b) {
    float rad = Vector2::AngleRad(a, b);
    float degree = rad * 180 / Math::PI;
    return degree ;
  }
  float Vector2::AngleRad(const Vector2 a, const Vector2 b) {
    //return std::acos(Vector2::Dot(a,b) / (a.Magnitude() * b.Magnitude()));
    float angle = std::atan2(a.y, a.x) - std::atan2(b.y, b.x); 
    return angle;
  }

  Vector2 Vector2::Up() {
    return Vector2(0,1);
  }
  Vector2 Vector2::Down() {
    return Vector2(0,-1);
  }
  Vector2 Vector2::Left() {
    return Vector2(-1,0);
  }
  Vector2 Vector2::Right() {
    return Vector2(1,0);
  }
  Vector2 Vector2::Zero() {
    return Vector2(0,0);
  }

  //Operators
  Vector2 Vector2::operator+(const Vector2& b) const {
    Vector2 a = *this;
    return Vector2(a.x + b.x, a.y + b.y);
  }
  //might not be the optimal solution
  Vector2 Vector2::operator-(const Vector2& b) const {
    Vector2 a = *this;
    return a + (-b);
  }
  Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
  }
  Vector2 Vector2::operator*(const float& scalar) const{
    return Vector2(x * scalar, y * scalar);
  }
  Vector2 Vector2::operator/(const float& scalar) const{
    return Vector2(x / scalar, y / scalar);
  }
  Vector2 Vector2::operator*(const Vector2& b) const{
    return Vector2(x * b.x, y * b.y);
  }
  Vector2 Vector2::operator/(const Vector2& b) const{
    return Vector2(x / b.x, y / b.y);
  }


  Vector2& Vector2::operator+=(const Vector2& b) {
    *this = *this + b;
    return *this;
  }
  Vector2& Vector2::operator-=(const Vector2& b) {
    *this = *this - b;
    return *this;
  }
  Vector2& Vector2::operator*=(const float& scalar) {
    *this = *this * scalar;
    return *this;
  }
  Vector2& Vector2::operator/=(const float& scalar) {
    *this = *this / scalar;
    return *this;
  }

  bool Vector2::operator==(const Vector2& b) const {
    Vector2 a = *this;
    bool xTrue = a.x == b.x;
    bool yTrue = a.y == b.y;
    return xTrue && yTrue;
  }

  bool Vector2::operator!=(const Vector2& b) const {
    Vector2 a = *this;
    bool xTrue = a.x == b.x;
    bool yTrue = a.y == b.y;
    return !(xTrue && yTrue);
  }
}
