#pragma once

// #include "platform/linux/v6-window.h"
#include "core.h"
#include "events/application-event.h"
#include "events/event.h"
#include "layer-stack.h"
#include "window.h"

namespace v6 {

class Application {
private:
  std::unique_ptr<Window> pWindow;

  bool running = true;
  bool onWindowClosed(WindowCloseEvent &e);
  LayerStack layerStack;

  static Application *sInstance;
  // static void setAppInstance(Application *pInstance) {
  //   v6::Application::sInstance = pInstance;
  // }

public:
  Application(/* args */);
  virtual ~Application();
  void run();
  void onEvent(Event &e);
  void pushLayer(Layer *layer);
  void pushOverlay(Layer *layer);
  inline Window &getWindow() { return *pWindow; }
  inline static Application &get() { return *sInstance; }
};

} // namespace v6
