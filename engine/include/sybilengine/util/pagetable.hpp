#pragma once
#include "sybilengine/util/freelist.hpp"

namespace sbl {
  static const unsigned int PAGE_SIZE = 4096;

  template<class T>
  struct Page {
    T data[PAGE_SIZE];
  };

  template<class T>
  class PageTable {
  public:
    void Add(const T& data);
    void Delete(const int id);
    T& operator [](const int idx);
    const T& operator [](const int idx) const;
    const std::vector<T>& GetData() const;

  private:
    FreeList<Page<T>*> m_table;
  };

  inline unsigned int IdxToPage(const int idx) {
    return idx % PAGE_SIZE;
  }

  template<class T>
  void PageTable<T>::Add(const T& data) {
  }
}
