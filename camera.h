#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Camera
{
public:
  Camera(int width, int height, float fov, float near, float far);
  ~Camera();

  glm::mat4 getViewMatrix()
  {
    view = glm::lookAt(position, position + direction, up);
    return view;
  };

  glm::mat4 getProjectionMatrix() const { return projection; };

  glm::vec3 getPosition() const { return position; };
  glm::vec3 getDirection() const { return direction; };

  void setAspectRatio(int width, int height);
  void setSpeed(float value) { speed = value; };

  void moveX(float amount);
  void moveY(float amount);
  void moveZ(float amount);
  void look(double x, double y);

private:
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  glm::vec3 direction{0.0f, 0.0f, -1.0f};
  glm::vec3 up{0.0f, 1.0f, 0.0f};
  glm::vec2 prevCursor{0.0f, 0.0f};

  glm::mat4 view;
  glm::mat4 projection;

  float fov;
  float near;
  float far;
  float aspectRatio;
  float speed = 1.0f;
  float sensibility = 0.1f;
};
