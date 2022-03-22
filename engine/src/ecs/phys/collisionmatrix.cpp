#include "sybilengine/ecs/phys/collisionmatrix.hpp"

namespace sbl {
  void CollisionMatrix::AddCollision(const int a, const int b) {
    if (a >= 0 && a < 64 && b >= 0 && b < 64) {
      matrix[a][b] = true;
    }
  }

  void CollisionMatrix::RemoveCollision(const int a, const int b) {
    if (a > 0 && a < 64 && b > 0 && b < 64) {
      matrix[a][b] = false;
    }
  }

  bool CollisionMatrix::GetCollision(const int a, const int b) const {
    if (a >= 0 && a < BitMask::MASK_SIZE && b >= 0 && b < BitMask::MASK_SIZE) {
      return matrix[a][b];
    }
    return false;
  }
}