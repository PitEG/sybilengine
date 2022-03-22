#include "sybilengine/ecs/scene.hpp"
#include "sybilengine/ecs/transform.hpp"

namespace sbl {
  std::string Scene::GetName() const {
    return m_name;
  }

  unsigned int Scene::max_component_types = 0;

  Entity Scene::CreateEntity() {
    Entity e(m_currEntity++);
    Transform t;
    AddComponent<Transform>(e,t);
    return e;
  }

  bool Scene::DeleteEntity(const Entity& entity) {
    bool atLeastOne = false;
    for(int i = 0; i < m_components.size(); i++) {
      if (m_components[i] == nullptr) continue;
      atLeastOne = true;
      m_components[i]->DeleteComponent(entity);
    }

    return atLeastOne;
  }
}
