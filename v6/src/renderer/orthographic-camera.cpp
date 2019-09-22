#include "orthographic-camera.h"

#include <gtc/matrix_transform.hpp>

namespace v6 {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top)
    : projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      viewMatrix(1.0f) {
  viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::setProjection(float left, float right, float bottom,
                                       float top) {
  projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

  viewMatrix = glm::inverse(transform);
  viewProjectionMatrix = projectionMatrix * viewMatrix;
}

} // namespace v6
