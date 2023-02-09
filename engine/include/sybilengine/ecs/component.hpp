#pragma once 

#include "sybilengine/ecs/entity.hpp"

#include <vector>

namespace sbl {

  template<class T> 
  class Component {
  public:
    void Add(const Entity& e, const T& data);
    void Delete(const Entity& e);
    bool Contains(const Entity& e) const;
    T& Get(const Entity& e); // gets reference, lets you modify the data

  private:
    // map of entity id to this object's internal list of entities
    // this will be very sparse :/
    // -1 means not in here
    std::vector<int> m_entityIds; 

    // list of entities and their component
    // completely packed
    std::vector<unsigned int> m_entities;
    std::vector<T> m_data;
  };

  template<class T>
  void Component<T>::Add(const Entity& e, const T& data) {
    unsigned int idx = e.ID();
    if (m_entityIds.size() < idx) {
      m_entityIds.resize(idx);
    }
    m_entities.push_back(idx);
    m_entityIds[idx] = m_entities.size()-1;
  }

  template<class T>
  void Component<T>::Delete(const Entity& e) {
    unsigned int idx = e.ID();
    if (m_entityIds.size() < e.ID()) {
      return;
    }

    // removing entity,component and repacking 
    m_entityIds[idx] = -1;
    // remove element at idx and fill with last element
    m_entities[idx] = m_entities[m_entities.size()-1];
    m_data[idx] = m_entities[m_data.size()-1];
    // resize to delete the last element (which is the element at idx)
    m_entities.resize(m_entities.size()-1);
    m_data.resize(m_data.size()-1);
  }
}
