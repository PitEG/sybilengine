#include <catch2/catch_test_macros.hpp>
#include <sybilengine/util/idmap.hpp>

TEST_CASE("IdMap", "[IdMap]") {
  SECTION("Add/Remove/Get/Set/Exists") {
    sbl::IdMap<char> idmap;

    CHECK(0 == idmap.Add('a'));
    CHECK(1 == idmap.Add('b'));
    CHECK(2 == idmap.Add('c'));

    char a;
    CHECK(idmap.Get(0,a));
    CHECK(a == 'a');
    CHECK(idmap.Get(1,a));
    CHECK(a == 'b');
    
    CHECK(idmap.Remove(1));
    CHECK_FALSE(idmap.Remove(1));

    CHECK(1 == idmap.Add('d'));
    CHECK(3 == idmap.Add('e'));

    CHECK_FALSE(idmap.Remove(-1));
    CHECK_FALSE(idmap.Remove(4));

    CHECK(idmap.Get(2,a));
    CHECK(a == 'c');
    CHECK(idmap.Get(3,a));
    CHECK(a == 'e');

    for (int i = 0; i < 4; i++) {
      CHECK(idmap.Exists(i));
    }

    // remove all
    CHECK(idmap.Remove(0));
    CHECK(idmap.Remove(1));
    CHECK(idmap.Remove(2));
    CHECK(idmap.Remove(3));

    for (int i = 0; i < 4; i++) {
      CHECK_FALSE(idmap.Exists(i));
    }
  }
}