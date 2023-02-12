#include <sybilengine/ecs/scene.hpp>
#include <catch2/catch.hpp>

#include <type_traits>

TEST_CASE("Scene","[Scene]") {
  SECTION("default constructor") {
    sbl::Scene s;
    sbl::Scene* sp = new sbl::Scene;
    delete sp;
  }

  SECTION("add components") {
    sbl::Scene s;
    sbl::Component<int> i;
    sbl::Component<char> c;
    s.Insert(i);
    s.Insert(c);
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

  SECTION("view") {
    sbl::Scene s;
    sbl::Component<int> i;
    sbl::Component<char> c;
    s.Insert(i);
    s.Insert(c);
    sbl::Component<int>& ints = s.Get<int>();
    sbl::Component<char>& chars = s.Get<char>();
    sbl::Entity e(0);
    ints.Add(e, 2);
    chars.Add(e, 'b');

    auto filter = s.Filter<int,char>();
    CHECK(std::get<0>(filter)->Get(e) == 2);
    CHECK(std::get<1>(filter)->Get(e) == 'b');
    CHECK(s.IntersectEntity(filter, e) == true);

    // CHECK(view[0]->GetComponent() == 2);
  }

  SECTION("insert") {
    sbl::Scene s;
    sbl::Component<int> ints;
    sbl::Entity e(0);
    ints.Add(e, 2);
    s.Insert(ints);
    sbl::Component<int> ints_get = s.Get<int>();
    CHECK(ints_get.Get(e) == 2);
  }
}
