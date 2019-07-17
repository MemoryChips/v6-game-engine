#pragma once

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

  std::unique_ptr<Window> pWindow;
  ImGuiLayer *imGuiLayer;
  bool running = true;
  LayerStack layerStack;

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
