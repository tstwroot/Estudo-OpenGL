#include "graphics.h"
#include "mesh.h"

#include <vector>

#define CUBES_SIZE 40

int main(int argc, char *argv[])
{
  Graphics& graphics = Graphics::getInstance();
  graphics.initialize({ 800, 600, "tsEngine" });

  Shader cubeShader{"shaders/vertex.glsl", "shaders/fragment.glsl"};

  std::vector<std::vector<Mesh*>*> cubes;

  for(int i = 0; i < CUBES_SIZE; i++)
  {
    cubes.push_back(new std::vector<Mesh*>());
    for(int j = 0; j < CUBES_SIZE; j++)
    {
      cubes.at(i)->push_back(new Mesh{Cube()});
      cubes.at(i)->at(j)->translate(glm::vec3{(float)-i, 0.0f, (float)-j - 0.5f});
    }
  }
 
  while(!glfwWindowShouldClose(graphics.getWindow()))
  {
    graphics.beginFrame();

    for(int i = 0 < CUBES_SIZE; i < CUBES_SIZE; i++) 
      for(int j = 0; j < CUBES_SIZE; j++)
        graphics.renderMesh(*cubes.at(i)->at(j), cubeShader);
  
    graphics.debugFrame();
    graphics.endFrame();
  }

  graphics.terminate();

  return 0;
}
