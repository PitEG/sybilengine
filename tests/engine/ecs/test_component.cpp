#include <sybilengine/ecs/component.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Component", "[Component]") {
  SECTION("Constructor") {
    sbl::Entity e;
    sbl::Component<int> i;
    int num = 13;
    i.data = num;
    CHECK(i.data == num);
    sbl::Component<int>* ip = new sbl::Component<int>();
    ip->data = num;
    CHECK(ip->data == num);
    delete ip;

    char character = 's';
    sbl::Component<char> c(e,character);
    CHECK(c.data == character);
    sbl::Component<char>* cp = new sbl::Component<char>(e,character);
    CHECK(cp->data == character);
    delete cp;
  }

  SECTION("Enable/Disable") {
    sbl::Component<int> c;
    CHECK(c.active == true);
    c.Enable();
    CHECK(c.active == true);
    c.Disable();
    CHECK(c.active == false);
  }

/* this functionality is moved to component manager
  SECTION("Data/OriginalData") {
    sbl::Entity e;
    sbl::Component<int> c(e, 90);
    CHECK(c.data == c.originalData);
    c.data = !90;
    CHECK(c.data != c.originalData);
    c.Reset();
    CHECK(c.data == c.originalData);
  }
  */

  SECTION("ENTITY ID") {
    unsigned int id = 180;
    sbl::Entity e(id);
    sbl::Component<int> c(e, 90);
    CHECK(c.GetEntity().ID() == id);
  }
}