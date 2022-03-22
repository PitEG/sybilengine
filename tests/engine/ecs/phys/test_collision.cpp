
#include <sybilengine/ecs/phys/collider.hpp>
#include <sybilengine/ecs/phys/collision.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Collision", "[Collision]") {
  SECTION("Constructor") {
    sbl::Collider collider;
    sbl::Collision collision(collider);
    CHECK(collision.GetCollider().GetType() == sbl::Collider::Type::Rectangle);
  }
}