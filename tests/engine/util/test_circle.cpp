#include <sybilengine/util/circle.hpp>
#include <sybilengine/util/math.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Circle Methods", "[Cirlce]") {
  SECTION("Area") {
    sbl::Circle c;
    CHECK(c.Area() == sbl::Math::PI);
    c = sbl::Circle(sbl::Vec2f::Zero(), 2);
    CHECK(c.Area() == sbl::Math::PI * 4);
  }

  SECTION("Circumference") {
    sbl::Circle c;
    CHECK(c.Circumference() == sbl::Math::PI * 2);
    c = sbl::Circle(sbl::Vec2f::Zero(), 2);
    CHECK(c.Circumference() == sbl::Math::PI * 2 * 2);
  }
}

TEST_CASE("Cirlce Static Methods", "[Circle]") {
  SECTION("Overlap") {
    sbl::Circle a;
    sbl::Circle b;
    CHECK(sbl::Circle::Overlap(a, b));
    a.center = sbl::Vec2f::Right() * 1;
    CHECK(sbl::Circle::Overlap(a, b));
    a.center = sbl::Vec2f::Right() * 2;
    CHECK(sbl::Circle::Overlap(a, b));
    a.center = sbl::Vec2f::Right() * 2.0001f;
    CHECK(!sbl::Circle::Overlap(a, b));
  }
}
