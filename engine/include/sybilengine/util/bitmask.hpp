#pragma once

namespace sbl {
  class BitMask {
  public:
    static const unsigned int MASK_SIZE = 64;

    BitMask();

    static bool CheckCollision(const BitMask& a, const BitMask& b); 

    void AddBit(const unsigned int bit);
    void RemoveBit(const unsigned int bit);
    bool CheckBit(const unsigned int bit);

    inline long long GetMask() const { return m_mask; }

  private:
    unsigned long long m_mask = 0;
  };
}