#include "GLFW/glfw3.h"
#include "renderer/renderer.h"

#include "application.h"
#include "input.h"
#include "log.h"

namespace v6 {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application *Application::sInstance = nullptr;

Application::Application(/* args */) {
  V6_ASSERT(!sInstance, "Application already exists!")
  sInstance = this;

  pWindow = std::unique_ptr<Window>(Window::Create());
  pWindow->SetEventCallback(BIND_EVENT_FN(onEvent));

  imGuiLayer = new ImGuiLayer();
  pushOverlay(imGuiLayer);
}

void Application::pushLayer(Layer *layer) { layerStack.pushLayer(layer); }
void Application::pushOverlay(Layer *layer) { layerStack.pushOverlay(layer); }

void Application::onEvent(Event &e) {
  EventDispatcher d(e);
  d.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));
  // LOG_CORE_TRACE("{0}", e);
  for (auto it = layerStack.end(); it != layerStack.begin();) {
    (*--it)->onEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::run() {
  while (running) {
    for (Layer *layer : layerStack)
      layer->onUpdate();
    imGuiLayer->begin();
    for (Layer *layer : layerStack)
      layer->onImGuiRender();
    imGuiLayer->end();
    pWindow->OnUpdate();
  }
}

bool Application::onWindowClosed([[maybe_unused]] WindowCloseEvent &e) {
  running = false;
  return true;
}

} // namespace v6
