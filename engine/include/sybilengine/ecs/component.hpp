#pragma once

#include "sybilengine/ecs/entity.hpp"

namespace sbl {
  /**
   * @brief Template component that is a container for the 
   * actual component (ie: transform, sprite, health points, etc.)
   * To fit with the library, the data T should not need to be
   * deep copied to retain the data.
   */
  template<typename T>
  class Component {
  public:
    /**
     * @brief Current Value of data.
     */
    T data;
    /**
     * @brief If the object is active.
     */
    bool active = true;

    /**
     * @brief Construct a default Component object. It is tied to Entity id 0 and
     * initializes the data to be the default value of T.
     */
    Component() : Component(Entity(0), T()) {}

    /**
     * @brief Construct a new Component object.
     * 
     * @param entity The Entity to be tied to.
     * @param data The data to initialize with. It will set the original data
     * and data member variables to what `data` is.
     */
    Component(const Entity& entity, const T& data) 
    : m_entity(entity), data(data) {
    }

    /**
     * @brief Enable the object. Sets `active` to True.
     */
    void Enable() {
      active = true;
    }
    /**
     * @brief Disables the object. Sets `active` to False.
     */
    void Disable() {
      active = false;
    }
    /**
     * @brief Get the Entity object that this component is tied to.
     * 
     * @return Entity The Entity this component is tied to.
     */
    const Entity& GetEntity() const {
      return m_entity;
    }

  private:
    Entity m_entity;
  };
}
