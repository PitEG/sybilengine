#pragma once
#include "sybilengine/util/bitmask.hpp"

namespace sbl {
  struct CollisionMatrix {
    bool matrix[BitMask::MASK_SIZE][BitMask::MASK_SIZE] = {false};

    /**
     * @brief Enable collision one way
     * 
     * @param a The layer we are interested in.
     * @param b The layer that we want layer a to react with.
     */
    void AddCollision(const int a, const int b);

    /**
     * @brief Disable collision one way
     * 
     * @param a The layer were are interested in.
     * @param b The layer that we want layer a to not react with anymore.
     */
    void RemoveCollision(const int a, const int b);

    /**
     * @brief Check if a can collide with b.
     * 
     * @param a The layer we are interested in.
     * @param b The layer that we are checking if layer can collide with.
     * @return true If a can collide with b.
     * @return false If a cannot collide with b.
     */
    bool GetCollision(const int a, const int b) const;
  };
}