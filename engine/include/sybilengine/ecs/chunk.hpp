#pragma once

#include <vector>
#include "sybilengine/ecs/entity.hpp"

namespace sbl {
  /**
   * @brief Scenes can be comprised of chunks. This allows for
   * organization for whateverf purpose. It can allow for optimization,
   * splitting a scene into different levels, etc. 
   * 
   * Essentially, it's a list containing objects that live in
   * this chunk. 
   * 
   */
  class Chunk {
  public:
    Chunk() {} // move this out to a .cpp file
    /**
     * @brief Construct a new Chunk with a list of entities to include
     * 
     * @param entities 
     */
    Chunk(std::vector<Entity> entities);

    /**
     * @brief Add Entity to the chunk.
     * 
     * @param entity The Entity to add.
     * @return true If the entity wasn't already in the chunk and
     * it was succesfully added.
     * @return false If the entity was in the chunk already;
     */
    bool AddEntity(const Entity entity);

    /**
     * @brief Remove Entity from the chunk.
     * 
     * @param entity The Entity to remove.
     * @return true If the entity was in the chunk and was successfully 
     * removed.
     * @return false If the entity wasn't in the chunk.
     */
    bool RemoveEntity(const Entity entity);

    /**
     * @brief Get the Entities list.
     * 
     * @return std::vector<Entity>& A reference to the list of entities.
     */
    inline std::vector<Entity>& GetEntities() { return m_entities;}

  private:
    std::vector<Entity> m_entities;
  };
}