#include <sybilengine/ecs/scene.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Scene","[Scene]") {
  SECTION("default constructor") {
    sbl::Scene s;
    sbl::Scene* sp = new sbl::Scene;
    delete sp;
  }

  SECTION("add components") {
    sbl::Scene s;
    sbl::Component<int>& ints = s.Get<int>();
    sbl::Entity e(0);
    ints.Add(e, 2);

    sbl::Component<int>& ints_again = s.Get<int>();
    CHECK(ints_again.Get(e) == 2);

    sbl::Component<char>& chars = s.Get<char>();
    chars.Add(e,'a');

    sbl::Component<char>& chars_again = s.Get<char>();
    CHECK(chars_again.Get(e) == 'a');
  }
}
