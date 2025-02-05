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

  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
  projection = glm::perspective(
    glm::radians(45.0f),
    static_cast<float>(config.width)/config.height,
    0.1f,
    100.0f
  );

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

void Graphics::terminate()
{
  glfwTerminate();
}

void Graphics::beginFrame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::endFrame()
{
  glfwSwapBuffers(window); 
  glfwPollEvents();
}

void Graphics::renderMesh(Mesh& mesh, Shader& shader)
{
  shader.use();
  projection = glm::perspective(
    glm::radians(45.0f),
    static_cast<float>(config.width)/config.height,
    0.1f,
    100.0f
  ); 
  glm::mat4 mvp = projection * view * mesh.getModelMatrix();
  shader.setMat4("mvp", mvp);
  mesh.draw();
}

void Graphics::onResizeWindow(GLFWwindow* window, int width, int height)
{
  Graphics *instance = static_cast<Graphics*>(glfwGetWindowUserPointer(window));
  if(instance)
  {
    instance->config.width = width;
    instance->config.height = height;
    glViewport(0, 0, instance->config.width, instance->config.height);
  }
}
