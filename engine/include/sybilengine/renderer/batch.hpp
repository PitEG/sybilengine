#pragma once

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
    std::vector<float> vertices; //base vertex data
    Shader shader;
    FreeList<T> entries;

    Batch(const std::vector<float>& vertices, const Shader& shader, const unsigned int maxInstances);

    inline unsigned int Size() const {
      return entries.GetData().size();
    }
    int Add(const T& entry);
    bool Delete(const int id);
    // returns a reference so the user can modify this entry themself.
    T& Get(const int id);

    // maybe don't use these two functions, just use above
    // bool Modify(const int id, const T& entry);
    // template<class E>
    // bool Modify(const int id, const int pos, const E& component);

    // I don't really want to expose opengl stuff here
    unsigned int m_vao;
    unsigned int m_ibo;
  private:
    unsigned int m_vbo;
  };

  template<class T>
  Batch<T>::Batch(const std::vector<float>& vertices, const Shader& shader, const unsigned int maxInstances) 
  : vertices(vertices), shader(shader) {
    // :/
    // glGenVertexArrays(1, &m_vao);
    // glGenBuffers(1, &m_vbo);
    // glBindVertexArray(m_vao);
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // entries.GetData();
    // const std::vector<sbl::Sprite>& instances = entries.GetData();
    // glGenBuffers(1, &m_ibo);
    // glBindBuffer(GL_ARRAY_BUFFER, m_ibo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(T) * maxInstances, instances.data(), GL_STATIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)0);
    // glVertexAttribDivisor(1,1);
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(Sprite),(void*)(2*sizeof(float)));
    // glVertexAttribDivisor(2,1);
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
