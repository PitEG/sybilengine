#pragma once

namespace sbl {
  /* Entity serves as an id that associates components together.
   * And ID of 0 is essentially a null Entity. 
   */
  struct Entity {
  public:
    Entity() : m_id(0) {}
    Entity(const unsigned int id) : m_id(id) {}

    inline unsigned int ID() const { return m_id; }

    friend inline bool operator==(const Entity& lhs, const Entity& rhs) {
      return lhs.ID() == rhs.ID();
    }

  private:
    unsigned int m_id;
  };
}
