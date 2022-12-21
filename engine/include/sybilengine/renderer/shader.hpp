#pragma once

#include <string>

namespace sbl {
  class Renderer;
  class Shader {
  friend Renderer;
  public:
    std::string vertex;
    std::string fragment;

    Shader(std::string vertex, std::string fragment);
    ~Shader();

    unsigned int GetShaderID() const;

    bool Set(std::string vertex, std::string fragment);
    bool SetVertex(std::string src);
    bool SetFragment(std::string src);

    bool Compile();

    const std::string& GetError() const;
  private:
    std::string m_vertexSrc;
    std::string m_fragmentSrc;
    std::string m_error;

    unsigned int m_vertexId;
    unsigned int m_fragmentId;
    unsigned int m_shaderId;
  };
}
