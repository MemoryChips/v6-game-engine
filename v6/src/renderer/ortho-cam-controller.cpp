#include "ortho-cam-controller.h"
#include "instrumentor.h"

#include "input.h"
#include "key-codes.h"

namespace v6 {

OrthoCamController::OrthoCamController(float aspectRatio, bool rotation)
    : aspectRatio(aspectRatio),
      camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel,
             zoomLevel),
      rotation(rotation) {}

void OrthoCamController::onUpdate(Timestep ts) {
  V6_PROFILE_FUNCTION();
  if (Input::isKeyPressed(V6_KEY_A))
    cameraPosition.x -= cameraTranslationSpeed * ts;
  else if (Input::isKeyPressed(V6_KEY_D))
    cameraPosition.x += cameraTranslationSpeed * ts;

  if (Input::isKeyPressed(V6_KEY_W))
    cameraPosition.y += cameraTranslationSpeed * ts;
  else if (Input::isKeyPressed(V6_KEY_S))
    cameraPosition.y -= cameraTranslationSpeed * ts;

  if (rotation) {
    if (Input::isKeyPressed(V6_KEY_Q))
      cameraRotation += cameraRotationSpeed * ts;
    if (Input::isKeyPressed(V6_KEY_E))
      cameraRotation -= cameraRotationSpeed * ts;

    camera.SetRotation(cameraRotation);
  }

  camera.SetPosition(cameraPosition);

  cameraTranslationSpeed = zoomLevel;
}

void OrthoCamController::onEvent(Event &e) {
  V6_PROFILE_FUNCTION();
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(
      V6_BIND_EVENT_FN(OrthoCamController::onMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      V6_BIND_EVENT_FN(OrthoCamController::onWindowResized));
}

bool OrthoCamController::onMouseScrolled(MouseScrolledEvent &e) {
  V6_PROFILE_FUNCTION();
  zoomLevel -= e.GetYOffset() * 0.25f;
  zoomLevel = std::max(zoomLevel, 0.25f);
  camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel,
                       -zoomLevel, zoomLevel);
  return false;
}

bool OrthoCamController::onWindowResized(WindowResizeEvent &e) {
  V6_PROFILE_FUNCTION();
  aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
  camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel,
                       -zoomLevel, zoomLevel);
  return false;
}

} // namespace v6