#pragma once

#include <sys/types.h>
#include <vector>
#include <functional>

#include "sybilengine/core/keycode.hpp"
#include "sybilengine/util/freelist.hpp"
#include "sybilengine/renderer/sprite.hpp"
#include "sybilengine/renderer/shader.hpp"
#include "sybilengine/renderer/texture.hpp"

#include <glad/glad.h>

namespace sbl {
  class Batch {
  public:
    enum VertexType {
      Float,
      Int,
    };
    // base vertex stuff
    std::vector<float> vertices; // actual vertices
    std::vector<unsigned int> vertexSizes; //sizes of each vertex 
                                           
    // instance info stuff
    std::vector<unsigned int> attribLocations;
    std::vector<unsigned int> attribSizes;
    std::vector<VertexType> attribType;
    std::vector<bool> attribNorm;
    Shader shader;
    // data
    void* data;

    Batch();
    Batch(const std::vector<float>& vertices, const Shader& shader);
  private:
  };

}
