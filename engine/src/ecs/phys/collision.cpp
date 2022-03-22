#include "sybilengine/ecs/phys/collision.hpp"
#include "sybilengine/ecs/phys/collider.hpp"

namespace sbl {
  Collision::Collision(const Collider& collider) 
  : m_collider(&collider) {
  }
}