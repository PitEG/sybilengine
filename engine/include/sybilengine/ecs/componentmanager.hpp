#pragma once

#include "sybilengine/ecs/component.hpp"
#include "sybilengine/ecs/entity.hpp"

#include <vector>
#include <unordered_map>

namespace sbl {
  /**
   * @brief A container for components of a specific type.
   * It maps an entity to a component (via the Entity's id).
   * It also saves an "original" value for a 
   * component, so it's redundant by a factor of 2.
   * 
   * Iterating through every element can be done like:
   * ```
   * ComponentManager<int> cm;
   * for (auto& component : cm) {
   *  // do stuff with component
   * }
   * ```
   */
  template<class T>
  class ComponentManager {
  public:

    /**
     * @brief Construct a default Component Manager object.
     */
    ComponentManager() {}

    /**
     * @brief Copy Constructor. 
     * Construct a new Component Manager object from another one.
     * 
     * @param src The ComponentManager to copy from.
     */
    ComponentManager(const ComponentManager& src) {
      *this = src;
    }

    /**
     * @brief Adds a component and mapps it to an entity. 
     * An entity can only have one of each component type, so it may not initialize
     * it if an entity is already associated with an existing one.
     * 
     * @param entity The Entity to tie the Component to.
     * @param data The data to initialize the Component with.
     * @param active If the Component is active or not.
     * @return true If the Component was successfully initialized and tied
     * to the Entity. 
     * @return false If the Entity is already associated with a component of this
     * type, it will return false
     */
    bool Add(const Entity& entity, const T& data = T(), bool active = true) {
      if (Find(entity) == true) { return false; }
      Component<T> component(entity, data);
      component.active = active;

      // map uses idx to point to the component in m_data
      m_data.push_back(component);
      m_originalData.push_back(component);
      m_entityComponentMap[entity.ID()] = (unsigned int) m_data.size() - 1; 

      return true;
    }

    /**
     * @brief Set the original data value of the Component associated with 
     * the given entity
     * 
     * @param entity The Entity that is associated with the Component we're editing
     * @param data The original value of T we would want for this Component
     * @return true If there is a Component associated with the given Entity
     * @return false If there is no Component assoicated with the given Entity
     */
    bool SetOriginal(const Entity& entity, const T& data) {
      if (Find(entity) == false) { return false; }

      int idx = m_entityComponentMap[entity.ID()];
      m_originalData[idx].data = data;
      return true;
    }

    /**
     * @brief The same as SetOriginal(const Entity&, const T& data) except
     * the original value is set to be the current value.
     * 
     * @param entity The Entity that is associated with the Component
     * @return true If there is a Component associated with the given Entity
     * @return false If there is no Component assoicated with the given Entity
     */
    bool SetOriginal(const Entity& entity) {
      if (Find(entity) == false) { return false; }

      int idx = m_entityComponentMap[entity.ID()];
      m_originalData[idx] = m_data[idx];
      return true;
    }

    /** 
     * @brief Returns a pointer into the argument if it exists
     * returns false if it doesn't exist.
     * 
     * @param entity Get the Component that belongs to this Entity.
     * @return Component<T>* The component requested. It may be a nullptr
     * if no Component is associated with the given Entity.
     */
    Component<T>* Get(const Entity& entity) {
      if (Find(entity) == false ) { return nullptr; }
      unsigned int idx = m_entityComponentMap[entity.ID()];
      return &(m_data[idx]);
    }

    Component<T>* GetOriginal(const Entity& entity) {
      if (Find(entity) == false ) { return nullptr; }
      unsigned int idx = m_entityComponentMap[entity.ID()];
      return &(m_originalData[idx]);
    }

    /** 
     * @brief Deletes component mapped to entity. Returns false if component doesn't exist
     * 
     * @param entity Delete the Component associated with this Entity.
     * @return true If the Component existed and was deleted.
     * @return false If the Component didn't exist.
     */
    bool Delete(const Entity& entity) {
      //TODO delete componenet
      if (Find(entity) == false) { return false; }

      unsigned int idx = m_entityComponentMap[entity.ID()]; 

      // erase routine for m_data
      Component<T>& temp = m_data[m_data.size() - 1];
      m_data[idx] = temp;
      m_data.resize(m_data.size() - 1);

      // erase routine for m_originalData
      Component<T>& tempOriginal = m_originalData[m_originalData.size() - 1];
      m_originalData[idx] = tempOriginal;
      m_originalData.resize(m_originalData.size() - 1);

      // change the idx of the moved component in the mapping
      const Entity& e = temp.GetEntity();
      m_entityComponentMap[e.ID()] = idx;

      m_entityComponentMap.erase(m_entityComponentMap.find(entity.ID()));

      return true;
    }

    /**
     * @brief Deletes every component.
     * 
     */
    void DeleteAll() {
      m_data.clear();
      m_entityComponentMap.clear();
    }

    /**
     * @brief Return the total number of Components.
     * 
     * @return unsigned int The total number of Components.
     */
    unsigned int Count() const {

      return m_data.size();
    }
    
    /**
     * @brief Total number of Components that is active
     * 
     * @return unsigned int The total number of active Components.
     */
    unsigned int CountActive() const {
      unsigned int count = 0;
      for (const Component<T>& c : m_data) {
        if (c.active) {
          count++;
        }
      }

      return count;
    }

    /**
     * @brief Enable all Components.
     */
    void EnableAll() {
      for(Component<T>& c : m_data) {
        c.Enable();
      }
    }
    /**
     * @brief Disable all Components.
     * 
     */
    void DisableAll() {
      for(Component<T>& c : m_data) {
        c.Disable();
      }
    }

    /**
     * @brief Get the vector of of all the components.
     * 
     * @return std::vector<Component<T>>& The list of Component Copies.
     */
    std::vector<Component<T>>& GetComponents() {
      return m_data;
    }

    std::vector<Component<T>>& GetOriginalComponents() {
      return m_originalData;
    }

    /**
     * @brief Works identically to the Get() function.
     * 
     * @param e 
     * @return Component<T>* A pointer to the component if the Entity e is mapped to one.
     */
    inline Component<T>* operator[](const Entity& e) {
      return Get(e);
    }

    // to enable the use of `for (auto& component : componentmanager)`
    using iterator = typename std::vector<Component<T>>::iterator;
    using const_iterator = typename std::vector<Component<T>>::const_iterator;
    iterator begin() { return m_data.begin(); }
    const_iterator begin() const { return m_data.begin(); }
    iterator end() { return m_data.end(); }
    const_iterator end() const { return m_data.end(); }

  private:
    std::unordered_map<unsigned int, unsigned int> m_entityComponentMap;
    std::vector<Component<T>> m_data;
    std::vector<Component<T>> m_originalData;

    /**
     * @brief Find the Component associated with the given Entity.
     * 
     * @param e The Entity associated with the component.
     * @return true If a Component was tied to the given Entity and was
     * found in the unordered map.
     * @return false If the Component tied to the given Entity doesn't exist.
     */
    bool Find(const Entity& e) {
      auto itr2 = m_entityComponentMap.find(e.ID());
      if(itr2 == m_entityComponentMap.end()) {
        return false;
      }
      return true;
    }
  };
}
