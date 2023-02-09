#pragma once 

#include "sybilengine/ecs/component.hpp"
#include "sybilengine/ecs/filter.hpp"

#include <tuple>

namespace sbl {
  class Scene {
    class ComponentEntry;

  public:
    template<class T>
    Component<T>& Get();

    template<class T>
    std::tuple<Component<T>*> Filter();
    template<class T1, class T2, class... Types>
    std::tuple<Component<T1>*, Component<T2>*, Component<Types>*...> Filter();

  private:
    static unsigned int MAX_COMPONENT_TYPES;
    std::vector<Entity> m_entities;
    std::vector<void*> m_components; // ComponentEntry

    template<class T>
    ComponentEntry* GetPointer();

  // BACKEND STUFF, SORTA UGLY
  private:
    class ComponentEntry {
    public:
      virtual void* GetComponent() { return nullptr; }
      // virtual unsigned int GetID() { return 0; }
    };
    template<class T>
    class ComponentGet : ComponentEntry {
    public:
      // unsigned int id = 0;
      Component<T> m_component;
      virtual void* GetComponent() {
        return (void*)&m_component;
      }
    };
  };
  template<class T>
  Scene::ComponentEntry* Scene::GetPointer() {
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

    // ComponentGet<T>* entry = (ComponentGet<T>*)(m_components[typeId]);
    // Component<T>* components = (Component<T>*)entry->GetComponent();
    // return *components;
    return (ComponentEntry*)(m_components[typeId]);
  }
  // END OF BACKEND STUFF

  template<class T>
  Component<T>& Scene::Get() {
    ComponentGet<T>* entry = (ComponentGet<T>*)(GetPointer<T>());
    Component<T>* components = (Component<T>*)entry->GetComponent();
    return *components;
  }

  // recursive stuff, my brain is tired
  template<class T>
  std::tuple<Component<T>*> Scene::Filter() {
    return std::tuple<Component<T>*>(&Get<T>());
  }
  template<class T1, class T2, class... Types>
  std::tuple<Component<T1>*, Component<T2>*, Component<Types>*...> Scene::Filter() {
    auto list = Filter<T2, Types...>();
    auto listHead = std::tuple<Component<T1>*>(&Get<T1>());
    return std::tuple_cat(listHead, list);
  }
}
