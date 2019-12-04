#pragma once

#include "v6-pch.h"
// #include "platform/linux/v6-window.h"
#include "core.h"
#include "events/application-event.h"
#include "events/event.h"
#include "imgui-layer/imgui-layer.h"
#include "layer-stack.h"
#include "window.h"
#include <memory>

namespace v6 {

class Application {
private:
  bool onWindowClosed(WindowCloseEvent &e);
  bool onWindowResize([[maybe_unused]] WindowResizeEvent &e);
  bool onKeyReleased([[maybe_unused]] KeyReleasedEvent &e);

  Scope<Window> pWindow;
  ImGuiLayer *imGuiLayer;
  bool running = true;
  bool minimized = false;
  LayerStack layerStack;
  double lastFrameTimeSec;
  static Application *sInstance;

public:
  Application(/* args */);
  virtual ~Application() = default;
  void run();
  void onEvent(Event &e);
  void pushLayer(Layer *layer);
  void pushOverlay(Layer *layer);
  inline Window &getWindow() { return *pWindow; }
  inline static Application &get() { return *sInstance; }
};

} // namespace v6
