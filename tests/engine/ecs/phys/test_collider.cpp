#include <sybilengine/ecs/phys/collider.hpp>
#include <sybilengine/util/math.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Collider", "[Collider]") {
  SECTION("Constructor") {
    // default collider constructor
    sbl::Collider collider;
    CHECK(collider.GetType() == sbl::Collider::Type::Rectangle);

    // rectangle collider constructor
    sbl::Rect rect;
    sbl::Collider colliderRect(rect, 1);
    CHECK(colliderRect.GetType() == sbl::Collider::Type::Rectangle);

    // cirlce collider constructor
    sbl::Circle circle;
    sbl::Collider colliderCircle(circle, 1);
    CHECK(colliderCircle.GetType() == sbl::Collider::Type::Circle);
  } 

  SECTION("Collision Layers") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);

    sbl::Collider rect1(sbl::Rect(sbl::Vec2f::Zero(), sbl::Vec2f(1,1)), 1);
    sbl::Collider circle1(sbl::Circle(sbl::Vec2f::Zero(),1), 1);

    CHECK(sbl::Collider::CalculateCollision(rect1,circle1,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle1,rect1,cm) == true);

    sbl::BitMask bmRec2;
    sbl::BitMask bmCirc2;
    bmRec2.AddBit(2);
    bmCirc2.AddBit(3);

    cm.AddCollision(4,1);

    sbl::Collider rect2(sbl::Rect(sbl::Vec2f::Zero(), sbl::Vec2f(1,1)), 4);
    sbl::Collider circle2(sbl::Circle(sbl::Vec2f::Zero(),1), 4);

    // check one way collisions
    CHECK(sbl::Collider::CalculateCollision(rect2,circle2,cm) == false);
    CHECK(sbl::Collider::CalculateCollision(circle2,rect2,cm) == false);
    CHECK(sbl::Collider::CalculateCollision(rect2,circle1,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle2,circle1,cm) == true);
  }
  
  SECTION("Kissing Rectangle Collider Collision") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);
    
    sbl::BitMask bm;
    bm.AddBit(1);
    sbl::Collider a(sbl::Rect(sbl::Vec2f(0,0), sbl::Vec2f(2,4)), 1);
    sbl::Collider b(sbl::Rect(sbl::Vec2f(2,0), sbl::Vec2f(2,4)), 1);
    sbl::Collider c(sbl::Rect(sbl::Vec2f(0,4), sbl::Vec2f(2,4)), 1);
    sbl::Collider d(sbl::Rect(sbl::Vec2f(2,4), sbl::Vec2f(2,4)), 1);

    // horizontal kissing
    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(b,a,cm) == true);
    // vertical kissing
    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(b,a,cm) == true);
    // corner kissing
    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(b,a,cm) == true);
  }

  SECTION("Calculate Overlapping Rectangle Collisions") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);

    sbl::Collider a(sbl::Rect(sbl::Vec2f(0,0), sbl::Vec2f(3,4)), 1);
    sbl::Collider b(sbl::Rect(sbl::Vec2f(1,2), sbl::Vec2f(5,7)), 1);
    sbl::Collider c(sbl::Rect(sbl::Vec2f(5,6), sbl::Vec2f(3,4)), 1);
    sbl::Collider d(sbl::Rect(sbl::Vec2f(2,0), sbl::Vec2f(1,6)), 1);

    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(a,c,cm) == false);
    CHECK(sbl::Collider::CalculateCollision(a,d,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(c,d,cm) == false);
  }

  SECTION("Calculate Kissing Circle Collision") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);

    sbl::Collider a(sbl::Circle(sbl::Vec2f::Zero(), 1), 1);
    sbl::Collider b(sbl::Circle(sbl::Vec2f(2,0), 1), 1);
    sbl::Collider c(sbl::Circle(sbl::Vec2f(0,2), 1), 1);
    // sqrt(2) LOL. Testing a collision at a 45 degree angle
    sbl::Collider d(sbl::Circle(sbl::Vec2f(1.41421356237309504,1.41421356237309504), 1), 1);

    // horizontal kissing
    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(b,a,cm) == true);
    // vertical kissing
    CHECK(sbl::Collider::CalculateCollision(a,c,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(c,a,cm) == true);

    // corner kissing
    CHECK(sbl::Collider::CalculateCollision(a,d,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(d,a,cm) == true);
  }

  SECTION("Calculate Overlapping Circle Collision") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);

    sbl::Collider a(sbl::Circle(sbl::Vec2f::Zero(), 1), 1);
    sbl::Collider b(sbl::Circle(sbl::Vec2f(2,0), 5), 1);
    sbl::Collider c(sbl::Circle(sbl::Vec2f(0,3), 1), 1);

    CHECK(sbl::Collider::CalculateCollision(a,b,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(b,a,cm) == true);

    CHECK(sbl::Collider::CalculateCollision(a,c,cm) == false);
    CHECK(sbl::Collider::CalculateCollision(c,a,cm) == false);

    CHECK(sbl::Collider::CalculateCollision(b,c,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(c,b,cm) == true);
  }

  SECTION("Calculate Kissing Rect and Circle Collisions") {
    sbl::CollisionMatrix cm;
    cm.AddCollision(1,1);

    sbl::Collider rect(sbl::Rect(sbl::Vec2f(0,0), sbl::Vec2f(3,4)), 1);
    sbl::Collider circle1(sbl::Circle(sbl::Vec2f(-1,1), 1), 1);
    sbl::Collider circle2(sbl::Circle(sbl::Vec2f(4,2), 1), 1);
    sbl::Collider circle3(sbl::Circle(sbl::Vec2f(2,-1), 1), 1);
    sbl::Collider circle4(sbl::Circle(sbl::Vec2f(2,5), 1), 1);
    sbl::Collider circle5(sbl::Circle(sbl::Vec2f(-sbl::Math::Sqrt(1.f/2),4 + sbl::Math::Sqrt(1.f/2)), 1), 1);

    // left side kiss
    CHECK(sbl::Collider::CalculateCollision(rect,circle1,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle1,rect,cm) == true);

    // left side kiss
    CHECK(sbl::Collider::CalculateCollision(rect,circle2,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle2,rect,cm) == true);

    // bottom side kiss
    CHECK(sbl::Collider::CalculateCollision(rect,circle3,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle3,rect,cm) == true);

    // top side kiss
    CHECK(sbl::Collider::CalculateCollision(rect,circle4,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle4,rect,cm) == true);

    // corner kiss
    CHECK(sbl::Collider::CalculateCollision(rect,circle5,cm) == true);
    CHECK(sbl::Collider::CalculateCollision(circle5,rect,cm) == true);
  }
}
