#pragma once  

namespace sbl {
  /**
   * @brief BufferBits enum. OpenGL has the Depth, Color, and Stencil Bits.
   * 
   */
  enum BufferBit {
    DepthBit,
    ColorBit,
    StencilBit
  };

  /**
   * @brief A mask that stores which BufferBit(s) are in use.
   */
  class BufferBits {
  private:
    unsigned int m_bitmask;
  public:
    /**
     * @brief Construct a new Buffer Bits object that has no buffers in it.
     * 
     */
    BufferBits() 
      : m_bitmask(0) {
    }

    /**
     * @brief Get the Buffer Bit mask.
     * 
     * @return const unsigned int The bitmask. 
     */
    inline const unsigned int GetBits() const { return m_bitmask; }

    /**
     * @brief Add a buffer bit to the bitmask.
     * 
     * @param bit The BufferBit to add.
     */
    void AddBit(BufferBit bit);
  };
}
