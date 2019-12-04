#include "application.h"

#include "GLFW/glfw3.h"
#include "renderer/renderer.h"

// #include "core/timestep.h"
// #include "input.h"
// #include "key-codes.h"
// #include "log.h"

namespace v6 {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application *Application::sInstance = nullptr;

Application::Application(/* args */) {

  V6_PROFILE_FUNCTION();
  V6_ASSERT(!sInstance, "Application already exists!")
  sInstance = this;

  pWindow = std::unique_ptr<Window>(Window::Create());
  pWindow->SetEventCallback(BIND_EVENT_FN(onEvent));

  Renderer::init();

  imGuiLayer = new ImGuiLayer();
  pushOverlay(imGuiLayer);
}

Application::~Application() {
  V6_PROFILE_FUNCTION();
  Renderer::shutdown();
}

void Application::pushLayer(Layer *layer) {
  V6_PROFILE_FUNCTION();
  layerStack.pushLayer(layer);
  layer->onAttach();
}
void Application::pushOverlay(Layer *layer) {
  V6_PROFILE_FUNCTION();
  layerStack.pushOverlay(layer);
  layer->onAttach();
}

void Application::onEvent(Event &e) {
  EventDispatcher d(e);
  d.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));
  d.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));
  d.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(onKeyReleased));
  // LOG_CORE_TRACE("{0}", e);
  for (auto it = layerStack.end(); it != layerStack.begin();) {
    (*--it)->onEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::run() {
  while (running) {
    double time = glfwGetTime();
    Timestep timestep = time - lastFrameTimeSec;
    lastFrameTimeSec = time;

    if (!minimized) {
      for (Layer *layer : layerStack)
        layer->onUpdate(timestep.getSeconds());
    }

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

bool Application::onWindowResize([[maybe_unused]] WindowResizeEvent &e) {
  auto w = e.GetWidth();
  auto h = e.GetHeight();
  // LOG_INFO("Window resize event with width: {0}, height: {1}", w, h);
  if (w == 0 || h == 0) {
    minimized = true;
    return false;
  }
  minimized = false;
  Renderer::onWindowResize(w, h);
  return false;
}

bool Application::onKeyReleased([[maybe_unused]] KeyReleasedEvent &e) {
  auto k = e.GetKeyCode();
  // LOG_INFO("Key released event with code: {0}", k);
  if (k == V6_KEY_ESCAPE) {
    LOG_WARN("Closing window with escape key: {0}", k);
    running = false;
    return true;
  }
  return false;
}

} // namespace v6
