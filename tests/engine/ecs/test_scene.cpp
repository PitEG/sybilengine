#include <sybilengine/ecs/scene.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Scene","[Scene]") {
  SECTION("default constructor") {
    sbl::Scene s;
    sbl::Scene* sp = new sbl::Scene;
    delete sp;
  }

  SECTION("add component") {
    sbl::Scene s;
    sbl::Component<int>& ints = s.Get<int>();
  }
}
