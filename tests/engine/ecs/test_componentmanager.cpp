#include <sybilengine/ecs/componentmanager.hpp>
#include <sybilengine/util/vector2.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "ComponentManager" , "[ComponentManager]") {
  SECTION("Constructor") {
    sbl::ComponentManager<int> cm;
    sbl::ComponentManager<int>* cmp = new sbl::ComponentManager<int>();
    
    CHECK(cm.Count() == 0);
    CHECK(cmp->Count() == 0);

    //custom types
    sbl::ComponentManager<sbl::Vector2> vcm;
    sbl::ComponentManager<sbl::Vector2>* vcmp = new sbl::ComponentManager<sbl::Vector2>();

    delete cmp;
    delete vcmp;
  }

  SECTION("Copy Constructor") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e(1);
    sbl::Entity e2(2);
    CHECK(cm.Add(e, 90));
    CHECK(cm.Count() == 1);
    sbl::ComponentManager<int> cmCopy(cm);
    CHECK(cmCopy.Count() == 1);
    CHECK(cm.Add(e2, 91));
    CHECK(cmCopy.Count() == 1);
  }

  SECTION("Add/Delete") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e(1);
    sbl::Entity e2(2);
    sbl::Entity e2_copy(2);

    CHECK(cm.Add(e, 90));
    CHECK(cm.GetComponents()[0].data == 90);
    CHECK(cm.GetOriginalComponents()[0].data == 90);
    CHECK(cm.Delete(e));
    CHECK_FALSE(cm.Delete(e2)); //delete something not there

    CHECK(cm.Add(e2, 180));
    CHECK_FALSE(cm.Add(e2, 180)); //double add
    CHECK(cm.GetComponents()[0].data == 180);
    CHECK(cm.GetOriginalComponents()[0].data == 180);
    CHECK(cm.Delete(e2));
    CHECK_FALSE(cm.Delete(e)); //delete something not there

    CHECK(cm.Count() == 0);
  }

  SECTION("Original Component Setting") {
    sbl::Entity e1(1);
    sbl::ComponentManager<int> cm;
    int num1 = 1;
    cm.Add(e1,num1);

    CHECK(cm.GetOriginal(e1)->data == num1);
    CHECK(cm.SetOriginal(e1, num1 + num1));
    CHECK(cm.GetOriginal(e1)->data == num1 + num1);
    cm.Get(e1)->data = num1 * 3;
    CHECK(cm.SetOriginal(e1));
    CHECK(cm.GetOriginal(e1)->data == num1 * 3);
  }

  SECTION("Mixed Add/Delete") {
    sbl::ComponentManager<int> cm;
    const int num1 = 1;
    const int num2 = 2;
    const int num3 = 3;

    sbl::Entity e1(1);
    sbl::Entity e2(2);
    sbl::Entity e3(3);

    CHECK(cm.Add(e1,num1));
    CHECK_FALSE(cm.Add(e1,num1));

    CHECK(cm.Add(e2,num2));
    CHECK(cm.Add(e3,num3));

    CHECK(cm.Delete(e2));
    CHECK(cm.Get(e3)->data == num3);
    CHECK(cm.Get(e1)->data == num1);
    CHECK(cm.GetOriginal(e3)->data == num3);
    CHECK(cm.GetOriginal(e1)->data == num1);

    CHECK(cm.Add(e2,num2));
    CHECK(cm.Get(e1)->data == num1);
    CHECK(cm.Get(e2)->data == num2);
    CHECK(cm.Get(e3)->data == num3);
    CHECK(cm.GetOriginal(e1)->data == num1);
    CHECK(cm.GetOriginal(e2)->data == num2);
    CHECK(cm.GetOriginal(e3)->data == num3);

    CHECK(cm.Delete(e1));
    CHECK(cm.Get(e2)->data == num2);
    CHECK(cm.Get(e3)->data == num3);
    CHECK(cm.GetOriginal(e2)->data == num2);
    CHECK(cm.GetOriginal(e3)->data == num3);

    CHECK(cm.Add(e1, num1));
    CHECK(cm.Get(e1)->data == num1);
    CHECK(cm.Get(e2)->data == num2);
    CHECK(cm.Get(e3)->data == num3);
    CHECK(cm.GetOriginal(e1)->data == num1);
    CHECK(cm.GetOriginal(e2)->data == num2);
    CHECK(cm.GetOriginal(e3)->data == num3);
    CHECK(cm.Delete(e1));
    CHECK(cm.Get(e2)->data == num2);
    CHECK(cm.Get(e3)->data == num3);
    CHECK(cm.GetOriginal(e2)->data == num2);
    CHECK(cm.GetOriginal(e3)->data == num3);
  }

  SECTION("Delete All") {
    sbl::ComponentManager<int> cm;

    int amount = 90;
    for(int i = 0; i < amount; i++) {
      sbl::Entity e(i);
      cm.Add(e, i);
    }
    CHECK(cm.Count() == amount);
    cm.DeleteAll();
    CHECK(cm.Count() == 0);
  }

  SECTION("Count") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e(0);

    cm.Add(e, 90);
    CHECK(cm.GetComponents()[0].data == 90);
    cm.Delete(e);
    CHECK(cm.Count() == 0);

    int amount = 123;
    for(int i = 0; i < amount; i++) {
      sbl::Entity e(i);
      cm.Add(e, i);
    }
    CHECK(cm.Count() == amount);

    for(int i = 0; i < amount; i++) {
      cm.Delete(sbl::Entity(i));
    }
    CHECK(cm.Count() == 0);
  }

  SECTION("CountActive") {
    sbl::ComponentManager<int> cm;

    int amount = 120;
    for(int i = 0; i < amount; i++) {
      sbl::Entity e(i);
      if (i % 2 == 0) { //is even, half of these should be active
        cm.Add(e, i, true);
      }
      cm.Add(e, i, false);
    }
    CHECK(cm.CountActive() == amount/2);
  }

  SECTION("Get") {
    sbl::Entity e(1);
    sbl::ComponentManager<int> cm;

    cm.Add(e, 9);
    sbl::Component<int>* something;
    CHECK(cm.Get(e));
    CHECK(cm.Get(e)->data == 9);
    CHECK_FALSE(cm.Get(sbl::Entity(39)));
    
  }

  SECTION("EnableAll/DisableAll") {
    sbl::ComponentManager<int> cm;

    int amount = 5;
    for (int i = 0; i < amount; i++) {
      cm.Add(sbl::Entity(i), i);
      CHECK(cm.Get(sbl::Entity(i)));
      CHECK(cm.Get(sbl::Entity(i))->data == i);
      CHECK(cm.Get(sbl::Entity(i))->active);
    }
    cm.DisableAll();
    for (int i = 0; i < amount; i ++) {
      CHECK(cm.Get(sbl::Entity(i)));
      CHECK_FALSE(cm.Get(sbl::Entity(i))->active);
    }
    cm.EnableAll();
    for (int i = 0; i < amount; i ++) {
      CHECK(cm.Get(sbl::Entity(i)));
      CHECK(cm.Get(sbl::Entity(i))->active);
    }
  }

  SECTION("GetComponents") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e(1);
    cm.Add(e, 90);
    CHECK(cm.GetComponents().size() == 1);
    CHECK(cm.GetComponents()[0].data == 90);
  }

/*
  SECTION("GetComponentsEnabled") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e1(1);
    sbl::Entity e2(2);
    cm.Add(e1, 1);
    cm.Add(e2, 2);
    //e1 e2 
    CHECK(cm.GetComponentsEnabled().size() == 2);
    cm.Get(e1)->Disable();
    //e2 
    CHECK(cm.GetComponentsEnabled().size() == 1);
    CHECK(cm.GetComponentsEnabled()[0].data == 2);
    cm.Get(e2)->Disable();
    //
    CHECK(cm.GetComponentsEnabled().size() == 0);
    cm.Get(e1)->Enable();
    //e1 
    CHECK(cm.GetComponentsEnabled().size() == 1);
    CHECK(cm.GetComponentsEnabled()[0].data == 1);
  }

  SECTION("GetPointers") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e(1);
    cm.Add(e, 90);
    CHECK(cm.GetPointers().size() == 1);
    CHECK(cm.GetPointers()[0]->data == 90);
  }

  SECTION("GetPointersEnabled") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e1(1);
    sbl::Entity e2(2);
    cm.Add(e1, 1);
    cm.Add(e2, 2);
    //e1 e2 
    CHECK(cm.GetPointersEnabled().size() == 2);
    cm.Get(e1)->Disable();
    //e2 
    CHECK(cm.GetPointersEnabled().size() == 1);
    CHECK(cm.GetPointersEnabled()[0]->data == 2);
    cm.Get(e2)->Disable();
    //
    CHECK(cm.GetPointersEnabled().size() == 0);
    cm.Get(e1)->Enable();
    //e1 
    CHECK(cm.GetPointersEnabled().size() == 1);
    CHECK(cm.GetPointersEnabled()[0]->data == 1);
  }
  */

  // this should just test to see if it compiles, nothing else
  SECTION("Ranger Iterator Syntax") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e1(1);
    cm.Add(e1, 2);
    for (auto& component: cm) {
      bool check = component.GetEntity() == e1 && component.data == 2;
      CHECK(check);
    }
  }

  SECTION("[] operator syntax") {
    sbl::ComponentManager<int> cm;
    sbl::Entity e1(1);
    cm.Add(e1, 2);
    sbl::Component<int>* i = cm[e1];
    CHECK((i != nullptr));
    CHECK((i->data == 2));
  }
}