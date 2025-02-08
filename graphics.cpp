#include "graphics.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

Graphics& Graphics::getInstance()
{
  static Graphics instance;
  return instance;
}

bool Graphics::initialize(const Configuration& config)
{
  this->config = config;

  if(glfwInit() == GLFW_FALSE)
    throw std::runtime_error("Failed to initialize GLFW");

  setupGLFW();
  setupOpenGL();
  setupImGui();

  camera = new Camera{config.width, config.height, 100.0f, 0.01f, 100.0f};

  return true;
}

void Graphics::setupGLFW()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);

  if(window == nullptr)
  {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(window, this);

  glfwSetFramebufferSizeCallback(window, onResizeWindow);
  glfwSetKeyCallback(window, onKeyEvent);
  glfwSetCursorPosCallback(window, onMouseMove);

  glfwMakeContextCurrent(window);
}

void Graphics::setupOpenGL()
{
  glewExperimental = GL_TRUE;

  if(glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW");

  glEnable(GL_DEPTH_TEST);

  glClearColor(config.clearColor.r, config.clearColor.g, config.clearColor.b, config.clearColor.a);
}

void Graphics::setupImGui()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = &ImGui::GetIO();
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glslVersion);
}

void Graphics::terminate()
{
  glfwTerminate();
}

void Graphics::beginFrame()
{
  currentTime = glfwGetTime();
  deltaTime = currentTime - lastFrameTime;
  lastFrameTime = currentTime;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(wireframeMode)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if(cursorEnabled)
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      camera->moveZ(1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      camera->moveZ(-1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera->moveX(1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera->moveX(-1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      camera->moveY(1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
      camera->moveY(-1.0f * deltaTime);

  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
      camera->setSpeed(10.0f);
  else
      camera->setSpeed(1.0f);
}

void Graphics::debugFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  
  if(showDebugUI)
  {
    ImGui::Begin("Debug"); 
    ImGui::Text("FPS: %.1f", io->Framerate);
    ImGui::Text("Timing: %.3f", 1000.0f / io->Framerate);

    if(ImGui::Checkbox("VSYNC", &vsyncOn))
      glfwSwapInterval(vsyncOn);

    ImGui::Text("Render mode");
    ImGui::Checkbox("Wireframe", &wireframeMode);

    ImGui::Text("Delta time: %f", deltaTime);

    glm::vec3 cameraPosition = camera->getPosition();
    glm::vec3 cameraDirection = camera->getDirection();
    ImGui::Text("Camera position: (%f %f %f)", cameraPosition.x, cameraPosition.y, cameraPosition.z);
    ImGui::Text("Camera direction: (%f %f %f)", cameraDirection.x, cameraDirection.y, cameraDirection.z);

    ImGui::End();
  }

  ImGui::Render();
  
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::endFrame()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Graphics::renderMesh(Mesh& mesh, Shader& shader)
{
  shader.use();

  glm::mat4 model = mesh.getModelMatrix();
  glm::mat4 view = camera->getViewMatrix();
  glm::mat4 projection = camera->getProjectionMatrix();

  shader.setMat4("model", model);
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  mesh.draw();
}

void Graphics::onResizeWindow(GLFWwindow* window, int width, int height)
{
  Graphics *instance = static_cast<Graphics*>(glfwGetWindowUserPointer(window));
  if(instance)
  {
    instance->config.width = width;
    instance->config.height = height;
    instance->camera->setAspectRatio(instance->config.width, instance->config.height);
    glViewport(0, 0, instance->config.width, instance->config.height);
  }
}

void Graphics::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  Graphics *instance = static_cast<Graphics*>(glfwGetWindowUserPointer(window));
  if(instance)
  {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      instance->cursorEnabled = !instance->cursorEnabled;

    if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
      instance->showDebugUI = !instance->showDebugUI;
  }
}

void Graphics::onMouseMove(GLFWwindow *window, double x, double y)
{
  Graphics *instance = static_cast<Graphics*>(glfwGetWindowUserPointer(window));
  if(instance)
    if(instance->cursorEnabled == false)
      instance->camera->look(x, y);
}
