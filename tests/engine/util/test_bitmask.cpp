#include <sybilengine/util/bitmask.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Bitmask", "[Bitmask]") {
  SECTION("Constructor") {
    sbl::BitMask bm;
  }

  SECTION("Adding/Removing Bits") {
    sbl::BitMask bm1;
    sbl::BitMask bm2;
    bm1.AddBit(0);
    bm2.AddBit(1);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
    bm1.AddBit(1);
    CHECK(sbl::BitMask::CheckCollision(bm1, bm2));
    bm2.AddBit(0);
    CHECK(sbl::BitMask::CheckCollision(bm1, bm2));
    bm2.RemoveBit(0);
    bm2.RemoveBit(1);
    bm2.RemoveBit(2);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
    bm1.RemoveBit(0);
    bm1.RemoveBit(1);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
    bm2.AddBit(63);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
    bm1.AddBit(63);
    CHECK(sbl::BitMask::CheckCollision(bm1, bm2));
  }

  SECTION("Adding/Removing Bits Out Of Bound") {
    sbl::BitMask bm1;
    sbl::BitMask bm2;
    bm1.AddBit(sbl::BitMask::MASK_SIZE);
    bm2.AddBit(sbl::BitMask::MASK_SIZE);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
    bm2.AddBit(-1);
    CHECK(!sbl::BitMask::CheckCollision(bm1, bm2));
  }

  SECTION("Check Bit") {
    sbl::BitMask bm;
    CHECK(!bm.CheckBit(0));
    CHECK(!bm.CheckBit(1));
    bm.AddBit(1);
    CHECK(!bm.CheckBit(0));
    CHECK(bm.CheckBit(1));
  }
}