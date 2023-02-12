#pragma once

#include "sybilengine/core.hpp"
#include "sybilengine/util.hpp"
#include "sybilengine/renderer.hpp"
#include "sybilengine/ecs.hpp"
#include "sybilengine/audio.hpp"

namespace sbl {
  class Engine {
  private:
  public:
    static void Init();
    static void Terminate();
  };
}
