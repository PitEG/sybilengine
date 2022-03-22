#pragma once

#include "sybilengine/ecs/entity.hpp"

#include <unordered_map>
#include <vector>
#include <string>

namespace sbl {
  /* Serves as an object pool that maps names to pools of objects
   * that should be alike. When querrying an object, it will 
   * return an object from that pool and cycles through them in order.
   */
  class EntityPool {
    /* Pool of entities. 
     */
    struct Pool {
      std::vector<Entity> entities;
      unsigned int        next; //keep track of who's next in line

      Entity& GetNext() {
        Entity& entity = entities[next];
        //increment next, and cycle if needed
        next++;
        if (next == entities.size()) {
          next = 0;
        }
        return entity;
      }
    };

  public:

    EntityPool();

    /* returns the entity that is mapped to a given name.
     * Entity of ID 0 is returned if it is not mapped.
     */
    Entity GetEntity(std::string& name);

    /* Add entity to a pool that is mapped to name
     */
    void AddEntity(std::string& name, Entity& entity);

  private:
    typedef std::unordered_map<std::string, Pool> map;
    map m_map;
  };
}
