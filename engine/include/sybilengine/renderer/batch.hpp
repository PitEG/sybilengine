#pragma once

#include <vector>

#include "sybilengine/util/freelist.hpp"
#include "sybilengine/renderer/sprite.hpp"

namespace sbl {
  template<class T> class Batch;

  using SpriteBach = Batch<Sprite>;

  template<class T>
  class Batch {
  public:
    std::vector<float> vertices; //base vertex data
    FreeList<T> entries;

    Batch(const std::vector<float>& vertices);

    int Add(const T& entry);
    bool Delete(const int id);
    // returns a reference so the user can modify this entry themself.
    T& Get(const int id);
    // maybe don't use these two functions, just use above
    bool Modify(const int id, const T& entry);
    template<class E>
    bool Modify(const int id, const int pos, const E& component);
  private:
  };

  template<class T>
  Batch<T>::Batch(const std::vector<float>& vertices) 
  : vertices(vertices) {
  }

  template<class T>
  int Batch<T>::Add(const T& entry) {
    return entries.Add(entry);
  }
  
  template<class T>
  bool Batch<T>::Delete(const int id) {
    return entries.Delete(id);
  }

  template<class T>
  T& Batch<T>::Get(const int id) {
    return entries[id];
  }

  template<class T>
  bool Batch<T>::Modify(const int id, const T& entry) {
    if (!entries.Contains(id)) { return false; }
    entries[id] = entry;
    return true;
  }

  template<class T>
  template<class E>
  bool Batch<T>::Modify(const int id, const int pos, const E& component) {
    if (!entries.Contains(id)) { return false; }
    entries[id][pos] = component;
    return true;
  }
}
