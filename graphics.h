#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shaders.h"
#include "mesh.h"
#include "camera.h"

#include "third-party/imgui/imgui.h"
#include "third-party/imgui/imgui_impl_opengl3.h"
#include "third-party/imgui/imgui_impl_glfw.h"

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
  void debugFrame();
  void endFrame();

  void renderMesh(Mesh& mesh, Shader& shader);
  
  float getDeltaTime() const { return deltaTime; };

  GLFWwindow* getWindow() const { return window ;};

  Graphics(const Graphics&) = delete;
  Graphics& operator=(const Graphics&) = delete;
private:
  Graphics() = default;

  GLFWwindow* window;
  Camera* camera;
  Configuration config;

  bool showDebugUI = false;
  bool wireframeMode = false;
  bool vsyncOn = true;
  bool cursorEnabled = true;

  ImGuiIO *io;

  const char *glslVersion = "#version 300 es";

  void setupGLFW();
  void setupOpenGL();
  void setupImGui();

  float lastFrameTime = 0.0f;
  float currentTime;
  float deltaTime;

  static void onResizeWindow(GLFWwindow* window, int width, int height);
  static void onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void onMouseMove(GLFWwindow *window, double x, double y);
};
