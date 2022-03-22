#include <sybilengine/ecs/phys/collider.hpp>
#include <sybilengine/ecs/phys/collidergrid.hpp>
#include <catch2/catch_test_macros.hpp>

bool EqualList(std::vector<int> a, std::vector<int> b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

TEST_CASE("CollisionGrid", "[CollisionGrid]") {
  SECTION("Constructor") {
    sbl::Rect bounds(-10,-10,20,20);
    sbl::ColliderGrid grid(bounds,5,10);
  }

  SECTION("Insert/Delete") {
    sbl::Rect bounds(-10,-10,20,20);
    sbl::ColliderGrid grid(bounds,5,5);

    sbl::Collider c1(sbl::Rect(1,1,3,3), 0);

    // inserting
    int id0 = grid.Add(c1);
    CHECK(id0 == 0);
    int id1 = grid.Add(c1);
    CHECK(id1 == 1);
    int id2 = grid.Add(c1);
    CHECK(id2 == 2);

    std::vector<sbl::Collision> collisions;
    grid.GetCollisions(id0,collisions);
    CHECK(collisions.size() == 2);
    grid.GetCollisions(id1,collisions);
    CHECK(collisions.size() == 2);
    grid.GetCollisions(id2,collisions);
    CHECK(collisions.size() == 2);

    CHECK(grid.Delete(id2));
    CHECK(grid.Delete(id0));
    CHECK(grid.Delete(id1));
  }

  /**
   * @brief Inserting out of grid bounds just clamps it to the closest cell
   */
  SECTION("Inserting Outside of Grid Bounds") { 
    sbl::Rect bounds(-10,-10,20,20);
    sbl::ColliderGrid grid(bounds,5,5);

    sbl::Collider c1(sbl::Rect(100,0,3,3), 0);

    // inserting
    int id0 = grid.Add(c1);
    CHECK(id0 == 0);
    int id1 = grid.Add(c1);
    CHECK(id1 == 1);
    int id2 = grid.Add(c1);
    CHECK(id2 == 2);

    std::vector<sbl::Collision> collisions;
    grid.GetCollisions(id0,collisions);
    CHECK(collisions.size() == 2);
    grid.GetCollisions(id1,collisions);
    CHECK(collisions.size() == 2);
    grid.GetCollisions(id2,collisions);
    CHECK(collisions.size() == 2);

    CHECK(grid.Delete(id2));
    CHECK(grid.Delete(id0));
    CHECK(grid.Delete(id1));
  }
  /*

    // removing
    CHECK_FALSE(grid.Delete(3));
    CHECK(grid.Delete(0));
    CHECK_FALSE(grid.Delete(0));

    // insert after removing one thing
    CHECK(0 == grid.Add(c1));
    CHECK(3 == grid.Add(c1));
    CHECK(4 == grid.Add(c1));

    // removing invalid ids
    CHECK_FALSE(grid.Delete(-1));
    CHECK_FALSE(grid.Delete(5));

    // remove all entities
    for (int i = 0; i < 5; i++) {
      CHECK(grid.Delete(i));
    }
  }

  SECTION("Move") {
    sbl::Rect bounds(-10,-10,20,20);
    sbl::ColliderGrid grid(bounds,5,5);

    sbl::Collider c1(sbl::Rect(1,1,3,3),0);
    int id0 = grid.Add(c1);
    int id1 = grid.Add(c1);
    int id2 = grid.Add(c1);
    int id3 = grid.Add(c1);

    grid.Move(id0, sbl::Vector2(-4,-4));
  }

  SECTION("Change") {
    sbl::Rect bounds(-10,-10,20,20);
    sbl::ColliderGrid grid(bounds,5,5);

    sbl::Collider c1(sbl::Rect(1,1,3,3),0);
    int id0 = grid.Add(c1);
    int id1 = grid.Add(c1);
    int id2 = grid.Add(c1);
    int id3 = grid.Add(c1);

    c1 = sbl::Collider(sbl::Rect(4,4,2,2),0);
    grid.Change(id1, c1);
  }
  */
}