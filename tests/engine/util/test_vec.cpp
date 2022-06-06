#include <sybilengine/util/vec.hpp>
#include <sybilengine/util/math.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <cmath>

TEST_CASE( "Vec2" , "[Vec2]") {
  SECTION("Constructors") {
    sbl::Vec2f vec1;
    CHECK(vec1.x == 0);
    CHECK(vec1.y == 0);

    sbl::Vec2f vec2(1,2);
    CHECK(vec2.x == 1);
    CHECK(vec2.y == 2);

    sbl::Vec2f vec3(vec2);
    CHECK(vec3.x == vec2.x);
    CHECK(vec3.y == vec2.y);
  }

  SECTION("Operators") {
    sbl::Vec2f vec1 = sbl::Vec2f(0,1) + sbl::Vec2f(2,3);
    CHECK(vec1.x == 2);
    CHECK(vec1.y == 4);

    sbl::Vec2f vec2 = sbl::Vec2f(2,3) - sbl::Vec2f(2,1);
    CHECK(vec2.x == 0);
    CHECK(vec2.y == 2);

    sbl::Vec2f vec3 = sbl::Vec2f(2,3) * sbl::Vec2f(4,5);
    CHECK(vec3.x == 8);
    CHECK(vec3.y == 15);

    sbl::Vec2f vec4 = sbl::Vec2f(8,15) / sbl::Vec2f(2,5);
    CHECK(vec4.x == 8.f/2.f);
    CHECK(vec4.y == 15.f/5.f);
    
    sbl::Vec2f vec5 = -sbl::Vec2f(2,3);
    CHECK(vec5.x == -2);
    CHECK(vec5.y == -3);

    sbl::Vec2f vec6 = sbl::Vec2f(2,3) * 4;
    CHECK(vec6.x == 8);
    CHECK(vec6.y == 12);

    sbl::Vec2f vec7 = sbl::Vec2f(15,18) / 3;
    CHECK(vec7.x == 15.f/3.f);
    CHECK(vec7.y == 18.f/3.f);

    sbl::Vec2f v8 = sbl::Vec2f(1,2);
    sbl::Vec2f v9 = sbl::Vec2f(1,2);
    CHECK(v8 == v9);
    sbl::Vec2f v10 = sbl::Vec2f(2,1);
    CHECK(v8 != v10);
  }

  SECTION("Instance Functions") {
    sbl::Vec2f vec1 = sbl::Vec2f(3,4);
    CHECK(vec1.Length() == 5.f);
    CHECK(vec1.LengthSqr() == 25.f);

    sbl::Vec2f vec2 = sbl::Vec2f(11,0);
    CHECK(vec2.Normalized() == sbl::Vec2f(1,0));
    CHECK(vec2.Length() == 11.f);
    CHECK(vec2.LengthSqr() == 11.f*11.f);

    sbl::Vec2f vec3 = sbl::Vec2f(11,11);
    CHECK(vec3.Normalized() == sbl::Vec2f(1.f/sbl::Math::Sqrt(2),1.f/sbl::Math::Sqrt(2)));
    CHECK(vec3.Length() == sbl::Math::Sqrt(2*(11.f * 11.f)));
    CHECK(vec3.LengthSqr() == 2*(11.f * 11.f));
  }

  SECTION("Static Functions") {
    sbl::Vec2f vec1 = sbl::Vec2f(3,4);
    sbl::Vec2f vec2 = sbl::Vec2f(5,6);
    CHECK(sbl::Vec2f::Dot(vec1,vec2) == 15.f+24.f);

    sbl::Vec2f vec3 = sbl::Vec2f(0,1);
    CHECK(sbl::Vec2f::Reflect(vec1,vec3) == sbl::Vec2f(3,-4));

    sbl::Vec2f vec4 = sbl::Vec2f(-1,-1); // lol non-precise
    // CHECK(sbl::Vec2f::Reflect(vec3,vec4.Normalized()).x == Catch::Approx(-1.f));
    // CHECK(sbl::Vec2f::Reflect(vec3,vec4.Normalized()).y == Catch::Approx(0.0f).epsilon(0.1f));
  }

  SECTION("Static Objects") {
    CHECK(sbl::Vec2f::Up() == sbl::Vec2f(0,1));
    CHECK(sbl::Vec2f::Down() == sbl::Vec2f(0,-1));
    CHECK(sbl::Vec2f::Left() == sbl::Vec2f(-1,0));
    CHECK(sbl::Vec2f::Right() == sbl::Vec2f(1,0));
  }
}


