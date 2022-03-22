#include "sybilengine/renderer/opengl/shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>


namespace sbl::gl {

  Shader::Shader(std::string vertexSrc, std::string fragmentSrc) {
    const char* vShaderCode = vertexSrc.c_str();
    const char* fShaderCode = fragmentSrc.c_str();
  
    //compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    //vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "ERROR, VERTEX SHADER FAILED TO COMPILE\n" << infoLog << '\n';
    }
    //fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      std::cout << "ERROR, FRAGMENT SHADER FAILED TO COMPILE\n" << infoLog << '\n';
    }
  
    //create program and link
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(id, 512, NULL, infoLog);
      std::cout << "ERROR, SHADER SHADERS FAILED TO LINK\n" << infoLog << '\n';
    }
  
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  Shader::Shader() {}

  Shader::~Shader() {
    if (id == 0) {
      return;
    }
    glDeleteProgram(id);
  }
  
  void Shader::Bind() const {
    int current_buffer;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_buffer);
    if (current_buffer == id) { return; }
    glUseProgram(id);
  }

  void Shader::Unbind() const {
    glUseProgram(0);
  }
  
  //TEMPLATE THESE MAYBE
  void Shader::SetBool(const std::string &name, bool value) {
    glUniform1i(GetUniformID(name), (int)value);
  }
  void Shader::SetInt(const std::string &name, int value) {
    glUniform1i(GetUniformID(name), value);
  }
  void Shader::SetFloat(const std::string &name, float value) {
    glUniform1f(GetUniformID(name), value); 
  }
  void Shader::SetVec2(const std::string &name, float x, float y) {
    glUniform2f(GetUniformID(name), x, y);
  }
  void Shader::SetVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(GetUniformID(name), x, y, z);
  }
  void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(GetUniformID(name), x, y, z, w);
  }
  void Shader::SetMat(const std::string &name, const glm::mat4 mat) {
    glUniformMatrix4fv(GetUniformID(name), 1, GL_FALSE, glm::value_ptr(mat));
  }
  
  int Shader::GetUniformID(const std::string name) {
    //if found return location id
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
      return uniformLocationCache[name];
    }
  
    //if not found, check if it exists, add it to map, and return it
    int location = glGetUniformLocation(id, name.c_str());
    if (location == -1) {
      std::cout << "WARNING: UNIFORM LOCATION FOR " << name << " DOESN'T EXIST\n";
    }
  
    uniformLocationCache[name] = location;
  
    return location;
  }
}
