#include <sybilengine/util/vector2.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>

TEST_CASE( "Vector2 Instance Methods" , "[Vector2]") {

  SECTION("Magnitude") {
    sbl::Vector2 v(10,0);
    CHECK(v.Magnitude() == 10);
    v = sbl::Vector2(0,10);
    CHECK(v.Magnitude() == 10);
    v = sbl::Vector2(4,3);
    CHECK(v.Magnitude() == 5);
  }

  SECTION("Normalize") {
    sbl::Vector2 v(10,0);
    CHECK(v.Normalize() == sbl::Vector2(1,0));
    v = sbl::Vector2(0,10);
    CHECK(v.Normalize() == sbl::Vector2(0,1));
    v = sbl::Vector2(4,3);
    float m = v.Magnitude();
    CHECK(v.Normalize() == sbl::Vector2(4.f/m, 3.f/m));
  }

  SECTION("Normal of Up/Down/Left/Right") {
    sbl::Vector2 v(4,0);
    v = v.Normal();
    CHECK(v == sbl::Vector2(0,4));
    v = v.Normal();
    CHECK(v == sbl::Vector2(-4,0));
    v = v.Normal();
    CHECK(v == sbl::Vector2(0,-4));
    v = v.Normal();
    CHECK(v == sbl::Vector2(4,0));
  }

  SECTION("Normal of Up/Down/Left/Right") {
    sbl::Vector2 v(3,2);
    v = v.Normal();
    CHECK(v == sbl::Vector2(-2,3));
    v = v.Normal();
    CHECK(v == sbl::Vector2(-3,-2));
    v = v.Normal();
    CHECK(v == sbl::Vector2(2,-3));
    v = v.Normal();
    CHECK(v == sbl::Vector2(3,2));
  }

  SECTION("Absolute") {
    sbl::Vector2 v(10,0);
    CHECK(v.Absolute() == sbl::Vector2(10,0));
    v = sbl::Vector2(-10,0);
    CHECK(v.Absolute() == sbl::Vector2(10,0));
    v = sbl::Vector2(0,10);
    CHECK(v.Absolute() == sbl::Vector2(0,10));
    v = sbl::Vector2(0,-10);
    CHECK(v.Absolute() == sbl::Vector2(0,10));
    v = sbl::Vector2(-10,-10);
    CHECK(v.Absolute() == sbl::Vector2(10,10));
    v = sbl::Vector2(10,10);
    CHECK(v.Absolute() == sbl::Vector2(10,10));
  }
}

TEST_CASE( "Vector2 Static Methods", "[Vector2]") {

  SECTION("Cardinal Unit Vectors") {
    CHECK(sbl::Vector2::Up()    == sbl::Vector2(0,1));
    CHECK(sbl::Vector2::Down()  == sbl::Vector2(0,-1));
    CHECK(sbl::Vector2::Left()  == sbl::Vector2(-1,0));
    CHECK(sbl::Vector2::Right() == sbl::Vector2(1,0));
  }

  SECTION("Reflect") {
    sbl::Vector2 v(std::sqrt(2), std::sqrt(2));
    sbl::Vector2 n(0,1);
    CHECK(sbl::Vector2::Reflect(v, n) == sbl::Vector2(-std::sqrt(2), std::sqrt(2)));
    n = sbl::Vector2(std::sqrt(2),std::sqrt(2));
    v = sbl::Vector2(1,0);
    CHECK(sbl::Vector2::Reflect(v, n) == sbl::Vector2(0,1));
    n = sbl::Vector2(-std::sqrt(2),-std::sqrt(2));
    v = sbl::Vector2(1,0);
    CHECK(sbl::Vector2::Reflect(v, n) == sbl::Vector2(0,1));
    n = sbl::Vector2(1,0);
    v = sbl::Vector2(std::sqrt(2), -std::sqrt(2));
    CHECK(sbl::Vector2::Reflect(v, n) == sbl::Vector2(std::sqrt(2), std::sqrt(2)));
  }

  SECTION("Dot Product") {
    sbl::Vector2 a(2,1);
    sbl::Vector2 b(-2,1);
    CHECK(sbl::Vector2::Dot(a,b) == -3);
    a = sbl::Vector2(3,4);
    b = sbl::Vector2(5,2);
    CHECK(sbl::Vector2::Dot(a,b) == 23);
  }

  SECTION("Distance") {
    sbl::Vector2 a(10,0);
    sbl::Vector2 b(0,0);
    CHECK(sbl::Vector2::Distance(a,b) == 10.f);
    a = sbl::Vector2(5,8);
    b = sbl::Vector2(2,4);
    CHECK(sbl::Vector2::Distance(a,b) == 5.f);
    a = sbl::Vector2(5,8);
    b = sbl::Vector2(8,12);
    CHECK(sbl::Vector2::Distance(a,b) == 5.f);
  }

  SECTION("AngleDegree") {
    float pi = atan(1) * 4;
    float radToDegree = 180 / pi;

    sbl::Vector2 a(0,1);
    sbl::Vector2 b(1,0);
    CHECK(sbl::Vector2::AngleDegree(a,b) == pi/2 * radToDegree);
    a = sbl::Vector2(std::sqrt(2), std::sqrt(2));
    CHECK(sbl::Vector2::AngleDegree(a,b) == pi/4 * radToDegree);
    a = b;
    b = sbl::Vector2(0,1);
    CHECK(sbl::Vector2::AngleDegree(a,b) == -pi/2 * radToDegree);

    a = sbl::Vector2(0,1);
    b = sbl::Vector2(-1,0);
    CHECK(sbl::Vector2::AngleDegree(a,b) == -pi/2 * radToDegree);
    b = sbl::Vector2(0,-1);
    CHECK(sbl::Vector2::AngleDegree(a,b) == pi * radToDegree);
    b = sbl::Vector2(std::sqrt(2),-std::sqrt(2));
    CHECK(sbl::Vector2::AngleDegree(a,b) == pi/4 * 3 * radToDegree);
  }

  SECTION("AngleRad") {
    float pi = atan(1) * 4;

    sbl::Vector2 a(0,1);
    sbl::Vector2 b(1,0);
    CHECK(sbl::Vector2::AngleRad(a,b) == pi / 2);
    a = sbl::Vector2(std::sqrt(2), std::sqrt(2));
    CHECK(sbl::Vector2::AngleRad(a,b) == pi / 4);
    a = b;
    b = sbl::Vector2(0,1);
    CHECK(sbl::Vector2::AngleRad(a,b) == -pi / 2);

    a = sbl::Vector2(0,1);
    b = sbl::Vector2(-1,0);
    CHECK(sbl::Vector2::AngleRad(a,b) == -pi/2);
    b = sbl::Vector2(0,-1);
    CHECK(sbl::Vector2::AngleRad(a,b) == pi);
    b = sbl::Vector2(std::sqrt(2),-std::sqrt(2));
    CHECK(sbl::Vector2::AngleRad(a,b) == pi/4 * 3);
  }

}

TEST_CASE( "Vector2 Operator Overrides", "[Vector2]") {
  SECTION("Addition/Subtraction") {
    sbl::Vector2 a(1,3);
    sbl::Vector2 b(2,4);
    CHECK(a + b == sbl::Vector2(a.x + b.x, a.y + b.y));
    b = sbl::Vector2(-30, -20);
    CHECK(a + b == sbl::Vector2(a.x + b.x, a.y + b.y));
  }

  SECTION("Scaler Multiplication/Division") {
    sbl::Vector2 a(1,3);
    float scalar = 3; 
    CHECK(a * scalar == sbl::Vector2(a.x * scalar, a.y * scalar));
    a = sbl::Vector2(-2,3);
    scalar = 3; 
    CHECK(a * scalar == sbl::Vector2(a.x * scalar, a.y * scalar));
    a = sbl::Vector2(-2,3);
    scalar = -3; 
    CHECK(a * scalar == sbl::Vector2(a.x * scalar, a.y * scalar));
  }

  SECTION("Component Wise Vector Multiplication/Division") {
    sbl::Vector2 a(1,3);
    sbl::Vector2 b(2,4);
    CHECK(a * b == sbl::Vector2(a.x * b.x, a.y * b.y));
    b = sbl::Vector2(-30, -20);
    CHECK(a * b == sbl::Vector2(a.x * b.x, a.y * b.y));
  }

  SECTION("Equality Comparison") {
    sbl::Vector2 a(1,3);
    sbl::Vector2 b(2,4);
    CHECK(a != b);
    b = sbl::Vector2(a.x, a.y);
    CHECK(a == b);
  }
}

