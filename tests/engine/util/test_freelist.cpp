#include <sybilengine/util/freelist.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("FreeList" , "[FreeList]") {
  SECTION("insertion/deletion") {
    sbl::FreeList<int> list;

    // simple insertion
    int id0 = list.Add(0);
    int id1 = list.Add(1);
    int id2 = list.Add(2);
    int id3 = list.Add(3);
    CHECK(list[id0] == 0);
    CHECK(list[id1] == 1);
    CHECK(list[id2] == 2);
    CHECK(list[id3] == 3);

    // delete one thing
    list.Delete(id0);
    id0 = list.Add(4);
    CHECK(list[id0] == 4);
    CHECK(list[id1] == 1);
    CHECK(list[id2] == 2);
    CHECK(list[id3] == 3);

    // delete 3 things, add 3 things
    list.Delete(id0);
    list.Delete(id1);
    list.Delete(id2);
    id0 = list.Add(5);
    id1 = list.Add(6);
    id2 = list.Add(7);
    CHECK(list[id0] == 5);
    CHECK(list[id1] == 6);
    CHECK(list[id2] == 7);
    CHECK(list[id3] == 3);

    // add 2 things to expand capacity
    int id4 = list.Add(8);
    int id5 = list.Add(9);
    CHECK(list[id4] == 8);
    CHECK(list[id5] == 9);

    // delete those 2 things immediately
    list.Delete(id4);
    list.Delete(id5);

    // delete again, shouldn't break data structure
    list.Delete(id4);
    list.Delete(id5);
  }
}