#include "sybilengine/util/bitmask.hpp"

namespace sbl {

  BitMask::BitMask() : m_mask(0) {
  }

  bool BitMask::CheckCollision(const BitMask& a, const BitMask& b) {
    if ((a.m_mask & b.m_mask) != 0) {
      return true;
    }
    else {
      return false;
    }
  }

  void BitMask::AddBit(const unsigned int bit) {
    if (bit < MASK_SIZE && bit >= 0) {
      m_mask = m_mask | (0x1 << bit); // OR
    }
  };

  void BitMask::RemoveBit(const unsigned int bit) {
    if (bit < MASK_SIZE && bit >= 0) {
      m_mask = m_mask ^ (0x1 << bit); // XOR
    }
  }

  bool BitMask::CheckBit(const unsigned int bit) {
    if (bit < MASK_SIZE && bit >= 0) {
      if ((m_mask & (0x1 << bit)) != 0) {
        return true;
      }
      return false;
    }
    return false;
  }
}