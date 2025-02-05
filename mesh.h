#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>

struct Cube
{
  std::vector<float> vertices = {
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
      -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f
  };

  std::vector<unsigned int> indices = {
      0, 1, 2, 2, 3, 0,
      4, 5, 6, 6, 7, 4,
      0, 4, 7, 7, 3, 0,
      1, 5, 6, 6, 2, 1, 
      3, 2, 6, 6, 7, 3,
      0, 1, 5, 5, 4, 0
  };
};

class Mesh
{
public:
  Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
  Mesh(const Cube& cube);
  ~Mesh();

  void draw();
  void rotate(glm::vec3 direction, float amount);
  void translate(glm::vec3 direction);

  glm::mat4 getModelMatrix() const { return modelMatrix; };
private:
  unsigned int VAO, VBO, EBO;
  size_t indexCount;
  
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  void setupMesh();
};
