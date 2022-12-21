#include "sybilengine/renderer/shader.hpp"

#include <glad/glad.h>

namespace sbl {
  Shader::Shader(std::string vertex, std::string fragment) {

    m_vertexSrc = vertex.c_str();
    m_fragmentSrc = fragment.c_str();

    m_vertexId = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    m_shaderId = glCreateProgram();

    // idk about this one 
    glAttachShader(m_shaderId, m_vertexId);
    glAttachShader(m_shaderId, m_fragmentId);
  }

  Shader::~Shader() {
    glDetachShader(m_shaderId, m_vertexId);
    glDetachShader(m_shaderId, m_fragmentId);

    glDeleteShader(m_vertexId);
    glDeleteShader(m_fragmentId);
    glDeleteProgram(m_shaderId);
  }

  bool Shader::Compile() {
    int success = 0;
    char log[512] = "";

    const char* vertexSrc = m_vertexSrc.c_str();
    const char* fragmentSrc = m_fragmentSrc.c_str();

    glShaderSource(m_vertexId, 1, &vertexSrc, nullptr);
    glCompileShader(m_vertexId);

    glGetShaderiv(m_vertexId, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(m_vertexId, sizeof(log), nullptr, log);
      m_error = std::string(log);
      return false;
    }

    glShaderSource(m_fragmentId, 1, &fragmentSrc, nullptr);
    glCompileShader(m_fragmentId);

    glGetShaderiv(m_fragmentId, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(m_fragmentId, sizeof(log), nullptr, log);
      m_error = std::string(log);
      return false;
    }

    glLinkProgram(m_shaderId);
    glGetProgramiv(m_shaderId, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(m_shaderId, sizeof(log), nullptr, log);
      m_error = std::string(log);
      return false;
    }

    return true;
  }

  const std::string& Shader::GetError() const {
    return m_error;
  }

  unsigned int Shader::GetShaderID() const {
    return m_shaderId;
  }
}
