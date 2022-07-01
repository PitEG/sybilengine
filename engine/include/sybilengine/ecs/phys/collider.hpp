#pragma once

#include "sybilengine/util/rect.hpp"
#include "sybilengine/util/circle.hpp"
#include "sybilengine/util/bitmask.hpp"
#include "sybilengine/ecs/phys/collision.hpp"
#include "sybilengine/ecs/phys/collisionmatrix.hpp"
#include "sybilengine/ecs/entity.hpp"
#include "sybilengine/ecs/phys/quadtree.hpp"

#include <vector>

namespace sbl {
  class Collider {
  public:
    enum Type {
      Circle,
      Rectangle
    };

    Collider();

    virtual ~Collider();

    Collider(const Collider& other);

    Collider(const sbl::Circle circle, const unsigned int layer, const Entity entity = Entity()); 
    Collider(const Rect rect, const unsigned int layer, const Entity entity = Entity());

    /**
     * @brief Get a reference to the list of collisions
     * 
     * @return std::vector<Collision>& A list of collisions
     */
    std::vector<Collision>& GetCollisions(); 

    /**
     * @brief Add a collision to the list of collisions.
     * 
     * @param collision The collision to add.
     */
    void AddCollision(const Collision& collision); 

    /**
     * @brief Get the Rect that encapsulates this object.
     * 
     */
    Rect GetCull() const;

    /**
     * @brief Get the Type of collider
     * 
     * @return Type The type of the collider
     */
    inline Type GetType() const { return m_type; }

    /**
     * @brief Get the Rectangle.
     * 
     * @return Rect If this collider isn't a Rect, this will be garbage. 
     */
    inline Rect GetRect() const { return space.rect; }

    /**
     * @brief Get the Circle.
     * 
     * @return Rect If this collider isn't a Circle, this will be garbage. 
     */
    inline sbl::Circle GetCircle() const { return space.circle; }

    void SetPosition(const Vec2f& pos);

    /**
     * @brief Calculate Collisions with a collision matrix. Checks only if
     * a can collide with b according to the Collision Matix.
     * 
     * @param a 
     * @param b 
     * @param cm 
     * @return true 
     * @return false 
     */
    static bool CalculateCollision(Collider& a, Collider& b, const CollisionMatrix& cm);

     /**
     * @brief Ignore layers and just check if they space overlaps/kisses.
     * 
     * @param a 
     * @param b 
     * @return true 
     * @return false 
     */
    static bool CalculateCollisionAlg(const Collider& a, const Collider& b);

  private:
    union Space {
      sbl::Rect rect;
      sbl::Circle circle;
    } space = {Rect(0,0,0,0)};

    Type m_type;
    unsigned int m_collisionLayer; // should be between [0,BITMASK_MAX) (so probably 0 to 63)
  };
}
