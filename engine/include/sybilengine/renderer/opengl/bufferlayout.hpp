#pragma once 

#include <vector>

namespace sbl::gl {
  struct LayoutElement {
    unsigned int count;
    unsigned int size; 
    unsigned int type; 
    unsigned char normalized;

  };

  class BufferLayout {
  public:
    BufferLayout();
    ~BufferLayout();

    /* maybe figure this out later
       template<typename T>
       void Push(unsigned int count, bool normalized);
     */

    void PushFloat(unsigned int count, bool normalized);
    void PushUnsignedInt(unsigned int count, bool normalized);
    //can add more specialized push functions

    inline const std::vector<LayoutElement>& Elements() const { return elements; }
    inline unsigned int Stride() const { return stride; }

  private:
    std::vector<LayoutElement> elements;
    unsigned int stride = 0;
  };

}
