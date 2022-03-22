#include "sybilengine/ecs/phys/collider.hpp"
#include "sybilengine/util/math.hpp"

#include "sybilengine/debug/logger.hpp"

namespace sbl {
  Collider::Collider() : Collider(Rect(), 0){
  }

  Collider::~Collider() {
  }

  Collider::Collider(const sbl::Circle circle, const unsigned int layer, const Entity entity) {
    m_type = Type::Circle;
    m_collisionLayer = layer;
    space.circle = circle;
  }

  Collider::Collider(const Rect rect, const unsigned int layer, const Entity entity) {
    m_type = Type::Rectangle;
    m_collisionLayer = layer;
    space.rect = rect;
  }

  void Collider::SetPosition(const Vector2& pos) {
    if (m_type == Type::Rectangle) {
      space.rect.SetPosition(pos);
    }
    else if (m_type == Type::Circle) {
      space.circle.center = pos;
    }
  }

  Rect Collider::GetCull() const {
    if (m_type == Type::Rectangle) {
      return space.rect;
    }
    else if (m_type == Type::Circle) { // Test Later
      float radius = space.circle.radius;
      Vector2 corner(radius, radius);
      Rect cull( space.circle.center - corner, space.circle.center + corner);
      return cull;
    }
    else { // failsafe
      return space.rect;
    }
  }

  bool RecCircleCollision(const Rect& rect, const Circle& circle) {
    // find the only possible collision point given position of circle and rect
    float xPos = Math::Clamp(circle.center.x, rect.BL().x, rect.BR().x);
    float yPos = Math::Clamp(circle.center.y, rect.BL().y, rect.TR().y);
    Vector2 posisbleCollisionPoint(xPos, yPos);

    float distance = Vector2::Distance(posisbleCollisionPoint, circle.center);
    if (distance <= circle.radius) {
      return true;
    }
    else {
      return false;
    }
  }

  bool Collider::CalculateCollision(Collider& a, Collider& b, const CollisionMatrix& cm) {
    bool checkA = cm.GetCollision(a.m_collisionLayer,b.m_collisionLayer);

    if (checkA && CalculateCollisionAlg(a,b)) {
      return checkA;
    }
    return false;
  }

  bool Collider::CalculateCollisionAlg(const Collider& a, const Collider& b) {
    bool collision = false;

    if (a.m_type == Type::Rectangle && b.m_type == Type::Rectangle) {
      const Rect& aRect = a.space.rect;
      const Rect& bRect = b.space.rect;
      Vector2 aBL = aRect.BL();
      Vector2 aTR = aRect.TR();
      Vector2 bBL = bRect.BL();
      Vector2 bTR = bRect.TR();
      // bool xCollision = (aRect.BL().x <= bRect.BR().x && aRect.BR().x >= bRect.BL().x);
      bool xCollision = (aBL.x <= bTR.x && aTR.x >= bBL.x);
      if (xCollision == false) { return false; }
      // bool yCollision = (aRect.BL().y <= bRect.TL().y && aRect.TL().y >= bRect.BL().y);
      bool yCollision = (aBL.y <= bTR.y && aTR.y >= bBL.y);
      if (yCollision == false) { return false; }
      collision = xCollision && yCollision;
    }
    else if (a.m_type == Type::Rectangle && b.m_type == Type::Circle) {
      if (RecCircleCollision(a.space.rect, b.space.circle)) {
        collision = true;
      }
    }
    else if (a.m_type == Type::Circle && b.m_type == Type::Rectangle) {
      if (RecCircleCollision(b.space.rect, a.space.circle)) {
        collision = true;
      }
    }
    else if (a.m_type == Type::Circle && b.m_type == Type::Circle) {
      const sbl::Circle& aCircle = a.space.circle;
      const sbl::Circle& bCircle = b.space.circle;

      float distance = sbl::Vector2::Distance(aCircle.center, bCircle.center);
      float radiusSum = aCircle.radius + bCircle.radius;

      collision = distance <= radiusSum;
    }

    return collision;
  }
}