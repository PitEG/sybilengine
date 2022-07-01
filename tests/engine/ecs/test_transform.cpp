#include <sybilengine/ecs/transform.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Transform Methods" , "[Transform]") {

  SECTION("default constructor") {
    sbl::Transform t;
    REQUIRE(t.position.x == 0);
    REQUIRE(t.position.y == 0);
    REQUIRE(t.layer == 0);
    REQUIRE(t.rotation == 0);
  }

  SECTION("constructor") {
    sbl::Transform t(sbl::Vec2f(10,10), 90, 1);
    REQUIRE(t.position == sbl::Vec2f(10,10));
    REQUIRE(t.rotation == 90);
    REQUIRE(t.layer == 1);
  }

  SECTION("translation") {
    sbl::Transform t;
    REQUIRE(t.position == sbl::Vec2f(0,0));
    t.Translate(sbl::Vec2f(3,3));
    REQUIRE(t.position == sbl::Vec2f(3,3));
    t.Translate(sbl::Vec2f(-10,10));
    REQUIRE(t.position == sbl::Vec2f(-7,13));
    t.Translate(sbl::Vec2f(-3,-9));
    REQUIRE(t.position == sbl::Vec2f(-10,4));
    t.Translate(sbl::Vec2f(1,-13));
    REQUIRE(t.position == sbl::Vec2f(-9,-9));
  }

  SECTION("rotation") {
    sbl::Transform t;
    REQUIRE(t.rotation == 0);
    t.Rotate(90);
    REQUIRE(t.rotation == 90);
    t.Rotate(360);
    REQUIRE(t.rotation == 450);
    t.Rotate(-450);
    REQUIRE(t.rotation == 0);
    t.Rotate(-170);
    REQUIRE(t.rotation == -170);
  }
}
