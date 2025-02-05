#include "shaders.h"
#include <fstream>
#include <iostream>
#include <GL/glew.h>

Shader::Shader(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath)
{
  loadVertexShader(vertexShaderFilepath);
  loadFragmentShader(fragmentShaderFilepath);
  programId = glCreateProgram(); 
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  int success;
  char info_log[512];
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(programId, 512, nullptr, info_log);
    std::cerr << info_log << '\n';
    return;
  }

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
}

Shader::~Shader()
{
  glDeleteProgram(programId);
}

std::vector<char> *Shader::readFile(const std::string &filepath)
{
  std::ifstream shaderFile{filepath, std::ios::binary};

  if(!shaderFile)
    return nullptr;

  shaderFile.seekg(0, std::ios::end);
  size_t file_size = shaderFile.tellg();
  shaderFile.seekg(0, std::ios::beg);
  
  std::vector<char> *file_content = new std::vector<char>(file_size);

  if(!shaderFile.read(file_content->data(), file_size))
    return nullptr;
  
  file_content->push_back(0);

  return file_content;
}

void Shader::loadVertexShader(const std::string &filepath)
{
  vertexShaderContent = readFile(filepath);

  if(vertexShaderContent == nullptr)
  {
    std::cerr << "Error: Can not read the shader file (" << filepath.c_str() << ")\n";
    return;
  }

  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  const char *vsc = vertexShaderContent->data();
  glShaderSource(vertexShaderId, 1, &vsc, nullptr); 
  glCompileShader(vertexShaderId);

  int success;
  char info_log[512];
  
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertexShaderId, 512, nullptr, info_log);
    std::cerr << info_log << '\n';
  }
}

void Shader::loadFragmentShader(const std::string &filepath)
{
  fragmentShaderContent = readFile(filepath);

  if(fragmentShaderContent == nullptr)
  {
    std::cerr << "Error: Can not read the shader file (" << filepath.c_str() << ")\n";
    return;
  }

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fsc = fragmentShaderContent->data();
  glShaderSource(fragmentShaderId, 1, &fsc, nullptr); 
  glCompileShader(fragmentShaderId);

  int success;
  char info_log[512];
  
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragmentShaderId, 512, nullptr, info_log);
    std::cerr << info_log << '\n';
  }
}

void Shader::use()
{
  glUseProgram(programId);
}

void Shader::setInt(const std::string &name, int &value) const
{
  glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setInt(const std::string &name, bool &value) const
{
  glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float &value) const
{
  glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, glm::vec2 &value) const
{
  glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, glm::vec3 &value) const
{
  glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, glm::vec4 &value) const
{
  glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string &name, glm::mat2 &value) const
{
  glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string &name, glm::mat3 &value) const
{
  glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
} 

void Shader::setMat4(const std::string &name, glm::mat4 &value) const
{
  glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
