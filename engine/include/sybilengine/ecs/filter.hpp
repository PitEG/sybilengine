#pragma once

#include "sybilengine/ecs/component.hpp"

#include <tuple>

namespace sbl {
  template<class... Types>
  class Filter {
  public:
    std::tuple<Component<Types>...> components;

    template<class T>
    Component<T>& Get();
  };
}
