#pragma once

#include <vector>

namespace sbl {
  class Collider; 

  /**
   * @brief Information about a collision. This should be held by
   * a collider and includes information on who it collided with (another 
   * collider object) and how it collided
   * 
   */
  class Collision {
  public:
    Collision(const Collider& collider);
    /**
     * @brief The collider that collided with us.
     */
    inline const Collider& GetCollider() { return *m_collider; }

  private:
    /**
     * @brief The collider that collided with us.
     */
    const Collider* m_collider;

  };
}