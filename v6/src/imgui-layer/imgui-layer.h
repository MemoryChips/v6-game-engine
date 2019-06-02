#pragma once

#include "layer.h"

#include "events/application-event.h"
#include "events/key-event.h"
#include "events/mouse-event.h"

namespace v6 {

class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void onAttach();
  void onDetach();
  void onUpdate();
  void onEvent(Event &event);

private:
  bool onMouseButtonPressedEvent(MouseButtonPressedEvent &e);
  bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
  bool onMouseMovedEvent(MouseMovedEvent &e);
  bool onMouseScrolledEvent(MouseScrolledEvent &e);
  bool onKeyPressedEvent(KeyPressedEvent &e);
  bool onKeyReleasedEvent(KeyReleasedEvent &e);
  bool onKeyTypedEvent(KeyTypedEvent &e);
  bool onWindowResizeEvent(WindowResizeEvent &e);

private:
  float m_Time = 0.0f;
};

} // namespace v6
