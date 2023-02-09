#pragma once

namespace sbl {

  class Entity {
  public:
    Entity();
    Entity(const unsigned int id);
    unsigned int ID() const;
  private:
    unsigned int m_id = 0;
  };
}
