#pragma once

#include "core/timestep.h"
#include "events/application-event.h"
#include "events/mouse-event.h"
#include "renderer/orthographic-camera.h"

namespace v6 {

class OrthoCamController {
public:
  OrthoCamController(float aspectRatio, bool rotation = false);

  void OnUpdate(Timestep ts);
  void OnEvent(Event &e);

  OrthographicCamera &GetCamera() { return m_Camera; }
  const OrthographicCamera &GetCamera() const { return m_Camera; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &e);
  bool OnWindowResized(WindowResizeEvent &e);

private:
  float m_AspectRatio;
  float m_ZoomLevel = 1.0f;
  OrthographicCamera m_Camera;

  bool m_Rotation;

  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  float m_CameraRotation = 0.0f;
  float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};

} // namespace v6