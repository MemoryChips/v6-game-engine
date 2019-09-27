#pragma once

#include "core/timestep.h"
#include "events/application-event.h"
#include "events/mouse-event.h"
#include "renderer/orthographic-camera.h"

namespace v6 {

class OrthoCamController {
public:
  OrthoCamController(float aspectRatio, bool rotation = false);

  void onUpdate(Timestep ts);
  void onEvent(Event &e);

  OrthographicCamera &GetCamera() { return camera; }
  const OrthographicCamera &GetCamera() const { return camera; }

  float getZoomLevel() { return zoomLevel; }
  void setZoomLevel(float level) { zoomLevel = level; }

private:
  bool onMouseScrolled(MouseScrolledEvent &e);
  bool onWindowResized(WindowResizeEvent &e);

private:
  float aspectRatio;
  float zoomLevel = 1.0f;
  OrthographicCamera camera;

  bool rotation;

  glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
  float cameraRotation = 0.0f;
  float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;
};

} // namespace v6