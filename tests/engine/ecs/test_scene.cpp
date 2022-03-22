#include <sybilengine/ecs/scene.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Scene Constructor" , "[Scene]") {
  SECTION("Default Constructor/Destructor") {
    sbl::Scene s;
    sbl::Scene* sp = new sbl::Scene;
    delete sp;
  }

  SECTION("Get Name") {
    sbl::Scene s("hello world");
    REQUIRE(s.GetName() == "hello world");
  }

  SECTION("Get ComponentManager") {
    sbl::Scene s;
    sbl::ComponentManager<int>& cm1 = s.GetComponents<int>();
    sbl::ComponentManager<int>& cm2 = s.GetComponents<int>();
    sbl::ComponentManager<char>& cm3 = s.GetComponents<char>();

    sbl::Entity e(1);
    int c = 90;
    int l = 'y';
    cm1.Add(e, c);
    cm3.Add(e, l);
    CHECK(cm1.Get(e));
    CHECK(cm1.Count() == 1);
    CHECK(cm2.Get(e));
    CHECK(cm2.Count() == 1);
    CHECK(cm3.Get(e));
    CHECK(cm3.Count() == 1);

    sbl::Scene s2;
    cm1 = s2.GetComponents<int>();
    cm2 = s2.GetComponents<int>();
    cm3 = s2.GetComponents<char>();

    CHECK(cm1.Count() == 0);
    CHECK(cm2.Count() == 0);
    CHECK(cm3.Count() == 0);

    cm1.Add(e, c);
    CHECK(cm1.Get(e));
    CHECK(cm1.Count() == 1);
    CHECK(cm2.Get(e));
    CHECK(cm2.Count() == 1);
    CHECK_FALSE(cm3.Get(e));
    CHECK(cm3.Count() == 0);
  }

  SECTION("Scene Destructor") {
    sbl::Scene s;
    s.GetComponents<int>();
    s.GetComponents<char>();

    sbl::Scene s2;
    s2.GetComponents<int>();

    sbl::Scene s3;
    s3.GetComponents<unsigned int>();

    sbl::Scene s4;
    s4.GetComponents<bool>();
  }

  SECTION("Scene Copy") {
    sbl::Scene s;
    sbl::ComponentManager<int>& ints = s.GetComponents<int>();
    sbl::ComponentManager<char>& chars = s.GetComponents<char>();

    sbl::Entity e(1);
    ints.Add(e, 80);
    chars.Add(e, 'J');

    sbl::Scene* copyS = new sbl::Scene(s);
    sbl::Scene copyCopyS(*copyS);
    const sbl::Scene copyConst(s);

    CHECK(ints.Get(e)->data == 80);
    CHECK(copyS->GetComponents<int>().Get(e)->data == 80);
    delete copyS;
    CHECK(ints.Get(e)->data == 80);
    CHECK(copyCopyS.GetComponents<int>().Get(e)->data == 80);
  }

  SECTION("Scene Add Component") {
    sbl::Scene s;
    sbl::ComponentManager<int>& ints = s.GetComponents<int>();
    sbl::ComponentManager<char>& chars = s.GetComponents<char>();

    sbl::Entity e(1);
    s.AddComponent<int>(e, 90);
    s.AddComponent<char>(e, 'c');

    CHECK(s.GetComponents<int>().Count() == 1);
    CHECK(s.GetComponents<char>().Count() == 1);

    CHECK(s.GetComponents<int>().Get(e)->data == 90);
    CHECK(s.GetComponents<char>().Get(e)->data == 'c');
  }

  SECTION("Scene Delete Components") {
    sbl::Scene s;
    sbl::ComponentManager<int>& ints = s.GetComponents<int>();
    sbl::ComponentManager<char>& chars = s.GetComponents<char>();

    int numEntities = 90;
    for (int i = 0; i < numEntities; i++) {
      sbl::Entity e(i);
      ints.Add(e, i);
    }
    CHECK(ints.Count() == numEntities);
    for (int i = 0; i < numEntities; i++) {
      sbl::Entity e(i);
      chars.Add(e, (char)i);
    }
    CHECK(chars.Count() == numEntities);

    s.DeleteEntity(sbl::Entity(1));
    CHECK(ints.Count() == numEntities - 1);
    CHECK(chars.Count() == numEntities - 1);
    CHECK(ints.Get(sbl::Entity(1)) == nullptr);
    CHECK(chars.Get(sbl::Entity(1)) == nullptr);
    CHECK(ints.Get(sbl::Entity(2))->data == 2);
    CHECK(chars.Get(sbl::Entity(2))->data == (char)2);

    s.DeleteAll();
    CHECK(ints.Count() == 0);
    CHECK(chars.Count() == 0);
  }
}