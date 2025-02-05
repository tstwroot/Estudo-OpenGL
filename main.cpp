#include "graphics.h"
#include "mesh.h"

int main(int argc, char *argv[])
{
  Graphics& graphics = Graphics::getInstance();
  graphics.initialize({ 800, 600, "tsEngine" });

  Shader cubeShader{"shaders/vertex.glsl", "shaders/fragment.glsl"};

  Cube cube1;
  Cube cube2;
  Cube cube3;

  Mesh cubeMesh1(cube1);
  Mesh cubeMesh2(cube2);
  Mesh cubeMesh3(cube3);

  cubeMesh2.translate({-1.5f, 3.0f, -10.0f});
  cubeMesh3.translate({3.0f, 1.0f, -5.0f});

  float lastFrameTime = 0.0f;
  float rotationSpeed = 1.0f;
  
  while(!glfwWindowShouldClose(graphics.getWindow()))
  {
    graphics.beginFrame();

    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    cubeMesh1.rotate({1.0f, 1.0f, 1.0f}, rotationSpeed * deltaTime);
    cubeMesh2.rotate({1.0f, 0.2f, 0.2f}, rotationSpeed * 0.5f * deltaTime);

    graphics.renderMesh(cubeMesh1, cubeShader);
    graphics.renderMesh(cubeMesh2, cubeShader);
    graphics.renderMesh(cubeMesh3, cubeShader);

    graphics.endFrame();
  }

  graphics.terminate();

  return 0;
}

