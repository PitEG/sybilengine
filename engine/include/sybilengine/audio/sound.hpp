#pragma once

#include <string>

namespace sbl {
  class Sound {
  public:
    void* data;

    Sound(const std::string& file);
  private:
  };
}
