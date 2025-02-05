#pragma once

#include <string>
#include <vector>

#include <glm/ext.hpp>

class Shader
{
public:
  Shader(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath);
  ~Shader();

  void loadVertexShader(const std::string &filepath);
  void loadFragmentShader(const std::string &filepath);
  void use();
  unsigned int getProgram() const { return programId; };

  void setInt(const std::string &name, int &value) const;
  void setInt(const std::string &name, bool &value) const;
  void setFloat(const std::string &name, float &value) const;
  void setVec2(const std::string &name, glm::vec2 &value) const;
  void setVec3(const std::string &name, glm::vec3 &value) const;
  void setVec4(const std::string &name, glm::vec4 &value) const;
  void setMat2(const std::string &name, glm::mat2 &value) const;
  void setMat3(const std::string &name, glm::mat3 &value) const;
  void setMat4(const std::string &name, glm::mat4 &value) const;
private:
  unsigned int vertexShaderId;
  unsigned int fragmentShaderId;
  unsigned int programId;

  std::vector<char>* readFile(const std::string &filepath);
  std::vector<char>* vertexShaderContent;
  std::vector<char>* fragmentShaderContent;


};
