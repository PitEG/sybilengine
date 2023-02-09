#pragma once 

#include "sybilengine/ecs/component.hpp"

namespace sbl {
  class Scene {
  public:
    template<class T>
    Component<T>& Get();

  private:
    static unsigned int MAX_COMPONENT_TYPES;
    std::vector<Entity> m_entities;
    std::vector<void*> m_components;

  // BACKEND STUFF, SORTA UGLY
  private:
    class ComponentEntry {
    public:
      virtual void* GetComponent() { return nullptr; }
      virtual unsigned int GetID() { return 0; }
    };
    template<class T>
    class ComponentGet : ComponentEntry {
    public:
      unsigned int id = 0;
      Component<T> m_component;
      virtual void* GetComponent() {
        return (void*)&m_component;
      }
    };
  // END OF BACKEND STUFF
  };

  template<class T>
  Component<T>& Scene::Get() {
    static unsigned int typeId = -1;
    
    // register if we're using a new component
    if (typeId == -1) {
      typeId = MAX_COMPONENT_TYPES++;
    }
    // resize registry if needed
    if (typeId >= m_components.size()) {
      m_components.resize(m_components.size() + typeId + 1, nullptr);
    }
    // if registry doesn't have entry, make one
    if (m_components[typeId] == nullptr) {
      m_components[typeId] = new ComponentGet<T>();
    }

    ComponentGet<T>* entry = (ComponentGet<T>*)(m_components[typeId]);
    Component<T>* components = (Component<T>*)entry->GetComponent();
    return *components;
  }
}

