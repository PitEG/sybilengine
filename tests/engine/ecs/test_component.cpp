#include <sybilengine/ecs/scene.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Component","[Component]") {
  SECTION("basic use") {
    sbl::Component<int> ints;
    sbl::Entity e1(1);
    sbl::Entity e2(2);

    ints.Add(e1, 10);
    ints.Add(e2, 23);
    CHECK(ints.Contains(e1) == true);
    CHECK(ints.Contains(e2) == true);
    CHECK(ints.Get(e1) == 10);
    CHECK(ints.Get(e2) == 23);
    CHECK(ints[e1] == 10);
    CHECK(ints[e2] == 23);

    ints.Delete(e1);
    ints.Delete(e2);
    CHECK(ints.Contains(e1) == false);
    CHECK(ints.Contains(e2) == false);
  }

  SECTION("view") {
  }
}
