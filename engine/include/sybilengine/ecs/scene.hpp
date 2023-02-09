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

    template<class... Types>
    std::tuple<Component<Types>...> Filter();

    template<class T1, class T2, class... Types>
    std::vector<ComponentEntry*> View();

    template<class T>
    std::vector<ComponentEntry*> View();

    // std::vector<ComponentEntry*> View() { return std::vector<ComponentEntry*>(); }

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

  template<class... Types>
  std::tuple<Component<Types>...> Scene::Filter() {
    return std::tuple<Component<int>,Component<char>>();
  }

  template<class T1, class T2, class... Types>
  std::vector<Scene::ComponentEntry*> Scene::View() {
    auto list = View<T2, Types...>();
    auto listHead = std::vector<Scene::ComponentEntry*>({GetPointer<T1>()});
    listHead.insert(listHead.end(),list.begin(),list.end());
    return listHead;
    // return std::vector<ComponentEntry*>();
  }

  template<class T>
  std::vector<Scene::ComponentEntry*> Scene::View() {
    ComponentEntry* entry = (ComponentEntry*)m_components[0];
    std::vector<ComponentEntry*> result;
    result.push_back(entry);
    return result;
  }
}
