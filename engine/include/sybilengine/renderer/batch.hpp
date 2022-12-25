#pragma once

#include <sys/types.h>
#include <vector>

#include "sybilengine/core/keycode.hpp"
#include "sybilengine/util/freelist.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/renderer/shader.hpp"

#include <glad/glad.h>

namespace sbl {
  template<class T> class Batch;

  using SpriteBatch = Batch<Sprite>;

  template<class T>
  class Batch {
  public:
    // base vertex stuff
    std::vector<float> vertices; // actual vertices
    std::vector<unsigned int> vertexSizes; //sizes of each vertex 
    FreeList<T> entries;
    // instance stuff
    std::vector<unsigned int> attribLocations;
    std::vector<unsigned int> attribSizes;
    std::vector<unsigned int> attribType;
    std::vector<unsigned int> attribNorm;
    Shader shader;

    Batch(const std::vector<float>& vertices, const Shader& shader, const unsigned int maxInstances = 1000 /* doesn't do anything */);
    Batch();

    inline unsigned int Size() const {
      return entries.Capacity();
    }
    int Add(const T& entry);
    bool Delete(const int id);
    // returns a reference so the user can modify this entry themself.
    T& Get(const int id);

    // maybe don't use these two functions, just use above
    // bool Modify(const int id, const T& entry);
    // template<class E>
    // bool Modify(const int id, const int pos, const E& component);
  private:
  };

  template<class T>
  Batch<T>::Batch(const std::vector<float>& vertices, const Shader& shader, const unsigned int maxInstances) 
  : vertices(vertices), shader(shader) {
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
}
