#include "sybilengine/ecs/entity.hpp"

namespace sbl {
  Entity::Entity() 
  : m_id(0) {
  }

  Entity::Entity(const unsigned int id) 
  : m_id(id) {
  }

  unsigned int Entity::ID() const {
    return m_id;
  }
}
