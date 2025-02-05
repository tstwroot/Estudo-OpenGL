#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shaders.h"
#include "mesh.h"

class Graphics
{
public:
  struct Configuration
  {
    int width = 800;
    int height = 600;
    const char *title = "Engine";
    glm::vec4 clearColor = {0.1f, 0.1f, 0.1f, 1.0f};
  };
  
  static Graphics& getInstance();

  bool initialize(const Configuration& config);
  void terminate();

  void beginFrame();
  void endFrame();

  void renderMesh(Mesh& mesh, Shader& shader);

  GLFWwindow* getWindow() const { return window ;};
  glm::mat4 getViewMatrix() const { return view; };
  glm::mat4 getProjectionMatrix() const { return projection; };

  Graphics(const Graphics&) = delete;
  Graphics& operator=(const Graphics&) = delete;
private:
  Graphics() = default;

  GLFWwindow* window;
  glm::mat4 view;
  glm::mat4 projection;
  Configuration config;

  void setupGLFW();
  void setupOpenGL();

  static void onResizeWindow(GLFWwindow* window, int width, int height);
};
