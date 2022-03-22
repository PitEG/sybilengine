#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include <unordered_map>
namespace sbl::gl {

  class Shader {
  public:
    /* Takes in src code for the vertex and fragment shaders. Both
     * are formatted like std::strings.
     */
    Shader(std::string vertexSrc, std::string fragmentSrc);
    /* Creates an empty program
     */
    Shader();
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void Destroy(); //put in destructor later?
  
    inline unsigned int ID() const { return id; }
  
    /*
     * Change Uniforms
     */
    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, float x, float y); 
    void SetVec3(const std::string &name, float x, float y, float z);
    void SetVec4(const std::string &name, float x, float y, float z, float w);
    void SetMat(const std::string &name, const glm::mat4);

  private:
    //shader program id
    unsigned int id = 0;
  
    //hasing program uniform id's
    std::unordered_map<std::string, int> uniformLocationCache;
    int GetUniformID(std::string name);

  };
}
