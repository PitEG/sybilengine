#pragma once

#include "sybilengine/ecs/component.hpp"

#include <tuple>

namespace sbl {
  template<class... Types>
  class Filter {
  public:
    Filter(std::tuple<Component<Types>...> components);

    template<class T>
    Component<T>& Get();

  private:
    std::vector<unsigned int> m_entities;
    std::tuple<Component<Types>...> m_components;
  };
}
