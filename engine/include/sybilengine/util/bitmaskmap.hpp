#pragma once

#include "sybilengine/util/bitmask.hpp"

#include <unordered_map>
#include <vector>
#include <string>

namespace sbl {
  class BitMaskMap {
  public:
    std::string GetString(unsigned long long bit);
    std::string GetMask(const std::string& string);
    void SetPair(const std::string& string, const long long bit);

  private:
    std::unordered_map<unsigned long long, std::string> m_toString;
    std::string strings[BitMask::MASK_SIZE];
  };
}