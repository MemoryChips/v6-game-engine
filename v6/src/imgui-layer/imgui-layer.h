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

  virtual void onAttach() override;
  virtual void onDetach() override;
  virtual void onImGuiRender() override;
  void begin();
  void end();

private:
  float m_Time = 0.0f;
};

} // namespace v6
