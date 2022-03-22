#pragma once

#include "sybilengine/ecs/entity.hpp"
#include "sybilengine/ecs/entitypool.hpp"
#include "sybilengine/ecs/component.hpp"
#include "sybilengine/ecs/componentmanager.hpp"
#include "sybilengine/ecs/chunk.hpp"

#include <string>

namespace sbl {
  /** 
   * @brief Acts as a container for Entities, Components (and ComponentManagers).
   * The access point for game logic. Make your own Update() functions
   * that manipulates the components that you add yourself. With the way components are
   * set up, this scene can be duplicated (so as long as components do 
   * not need to be deep copied to be functional).
   */
  class Scene {
  public:

    Scene() : m_name(std::string("default name")) {
    }

    Scene(const std::string& name) : m_name(name) {
      m_components.resize(max_component_types, nullptr);
    }

    //copy constructor
    Scene(const Scene& src) : Scene(src.m_name) {
      for(int i = 0; i < src.m_components.size(); i++) {
        if (src.m_components[i] != nullptr) {
          src.m_components[i]->Copy(src, *this);
        }
      }
    }

    virtual ~Scene() {
      for(int i = 0; i < m_components.size(); i++) {
        if (m_components[i] != nullptr) {
          delete m_components[i];
        }
      }
    }

    std::string GetName() const;

    template<class T>
    ComponentManager<T>& GetComponents() {
      return *(GetComponentsPointer<T>());
    }

    //creates an entity by making a transform component for it
    Entity CreateEntity();

    // deletes every component that has this entity
    bool DeleteEntity(const Entity& entity);

    // delete every entity and component
    void DeleteAll() {
      for (int i = 0; i < m_components.size(); i++) {
        if (m_components[i] == nullptr) continue;
        m_components[i]->DeleteAll();
      }
    }

    /**
     * @brief Creates a Chunk.
     * 
     * @param chunk 
     * @return true If the chunk name is not taken. It does not make a new one.
     * @return false If the chunk name is already taken.
     */
    bool CreateChunk(std::string chunk);

    /**
     * @brief Moves an entity from the gloabl chunk to a specific chunk
     * 
     * @param entity Entity to move.
     * @param chunk Chunk to move the Entity to.
     * @return true If the Entity exists and wasn't already in the chunk, and
     * moved successfully into the chunk.
     * @return false If the Entity doesn't exist or was already in the chunk.
     */
    bool MoveEntity(Entity entity, std::string chunk);

    /**
     * @brief Get a readonly list of Chunks
     * 
     * @return std::vector<Chunk>& The list of Chunks.
     */
    inline const std::vector<Chunk>& GetChunks() const;

    /**
     * @brief Activate all the Entities in a Chunk.
     * 
     * @param chunk The Chunk we want to activate.
     */
    void ActivateChunk(std::string chunk);

    /**
     * @brief Disable all the Entities in a Chunk.
     * 
     * @param chunk The Chunk we want to disable.
     */
    void DisableChunk(std::string chunk);

    //add a component id'ed with the entity and returns a pointer
    //the component
    template<class T>
    Component<T>* AddComponent(const Entity& entity, const T& component) {
      bool added = GetComponents<T>().Add(entity, component);
      if (added == false) return nullptr;
      return GetComponents<T>().Get(entity);
    }

    template<class T>
    bool DeleteComponent(const Entity& entity) {
      return GetComponents<T>().DeleteComponent(entity);
    }

    //TODO AddPool
    bool AddPool(const std::string& identifier, const Entity& entity, const unsigned int amount) {
      return false;
    }

    //TODO Check if entity exists, then add component to all instances of entity
    //with the given identifier, if it exists
    template<class T>
    bool AddPoolComponent(const std::string& identifier, const T& t) {
      return false;
    }

  private:
    //replace the current stuff with this new one
    class ComponentFunctorBase {
    public:
      virtual ~ComponentFunctorBase() {}
      unsigned int id = -1;
      virtual void Copy(const Scene& a, Scene& b) const {}
      virtual void* GetComponents() { return nullptr; }
      virtual bool DeleteComponent(const Entity& entity) { return false; }
      virtual void DeleteAll() {}
    };
    template<class T>
    class ComponentFunctor : public ComponentFunctorBase {
    public:
      ComponentFunctor(const unsigned int id) {
        this->id = id;
        components = new ComponentManager<T>();
      }
      ComponentFunctor(const ComponentFunctor<T>& src) {
        this->id = src.id;
        components = new ComponentManager<T>(*src.components);
      }
      virtual ~ComponentFunctor() override {
        delete components;
      }
      //components
      ComponentManager<T>* components;

      //functions
      virtual void Copy(const Scene& src, Scene& target) const override { 
        target.m_components[id] = (ComponentFunctorBase*)(new ComponentFunctor<T>(*this));
      }
      virtual void* GetComponents() override {
        return (void*)components;
      }
      virtual bool DeleteComponent(const Entity& entity) override { 
        return components->Delete(entity);
      }
      virtual void DeleteAll() override { 
        return components->DeleteAll();
      }
    };

  private:
    static unsigned int                 max_component_types;
    std::string                         m_name; 
    std::vector<ComponentFunctorBase*>  m_components; //use this when refactoring
    // std::vector<Chunk>                  m_chunks; // make this a hash map
    Chunk                               m_gloablChunk;

    unsigned int                        m_currEntity = 0;

  private:
    //Internal Usage. This is the backbone of the whole compnent
    //manager management (because it uses function static int id)
    template<class T>
    ComponentManager<T>* GetComponentsPointer() {
      static unsigned int typeId = -1;
      //if this is the first time this component type is added
      //to a scene, make register it 
      if (typeId == -1) {
        typeId = max_component_types++;
      }
      if (typeId >= m_components.size()) {
        m_components.resize(m_components.size() + typeId + 1, nullptr);
      }

      //if component manager doesn't exist, create it
      if (m_components[typeId] == nullptr) {
        m_components[typeId] = new ComponentFunctor<T>(typeId);
      }

      ComponentManager<T>* components = 
        (ComponentManager<T>*)(m_components[typeId]->GetComponents());
      return components;
    }
  };
}
