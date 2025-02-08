#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(int width, int height, float fov, float near, float far)
{
  this->fov = glm::radians(fov);
  this->near = near;
  this->far = far;
  this->aspectRatio = (float)width/(float)height;

  view = glm::lookAt(this->position, this->position + this->direction, this->up);
  projection = glm::perspective(this->fov, this->aspectRatio, this->near, this->far);
}

Camera::~Camera()
{

}

void Camera::setAspectRatio(int width, int height)
{
  aspectRatio = (float)width/(float)height;
  projection = glm::perspective(fov, aspectRatio, near, far);
}

void Camera::moveX(float amount)
{
  glm::vec3 right = glm::normalize(glm::cross(direction, up));
  position += right * amount * speed;
}

void Camera::moveY(float amount)
{
  position.y += amount * speed;
}

void Camera::moveZ(float amount)
{
  position += glm::normalize(direction) * amount * speed;
}

void Camera::look(double x, double y)
{
  glm::vec2 currentCursor{x, y};
  glm::vec2 deltaMotionCursor = currentCursor - prevCursor;

  float yaw = -deltaMotionCursor.x;
  float pitch = -deltaMotionCursor.y;

  yaw *= sensibility;
  pitch *= sensibility;

  const glm::vec3 right = glm::normalize(glm::cross(direction, up));
  const glm::mat4 identity = glm::identity<glm::mat4>();

  glm::mat4 yaw_rotation = glm::rotate(identity, glm::radians(yaw), up);
  glm::mat4 pitch_rotation = glm::rotate(identity, glm::radians(pitch), right);

  up = pitch_rotation * glm::vec4{up, 0.0f};
  direction = yaw_rotation * pitch_rotation * glm::vec4{direction, 0.0f};

  prevCursor = currentCursor;
}
