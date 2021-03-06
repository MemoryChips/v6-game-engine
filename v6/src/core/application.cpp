#include "application.h"

#include "GLFW/glfw3.h"
#include "core.h"
#include "renderer/renderer.h"

namespace v6 {

Application *Application::sInstance = nullptr;

Application::Application() {

  V6_PROFILE_FUNCTION();
  V6_ASSERT(!sInstance, "Application already exists!")
  sInstance = this;

  pWindow = Window::Create();
  pWindow->SetEventCallback(V6_BIND_EVENT_FN(Application::onEvent));

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
  V6_PROFILE_FUNCTION();
  EventDispatcher d(e);
  d.Dispatch<WindowCloseEvent>(V6_BIND_EVENT_FN(Application::onWindowClosed));
  d.Dispatch<WindowResizeEvent>(V6_BIND_EVENT_FN(Application::onWindowResize));
  d.Dispatch<KeyReleasedEvent>(V6_BIND_EVENT_FN(Application::onKeyReleased));

  // for (auto it = layerStack.end(); it != layerStack.begin();) {
  //   (*--it)->onEvent(e);
  //   if (e.Handled)
  //     break;
  // }

  for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
    {
      (*it)->onEvent(e);
      if (e.Handled)
        break;
    }
  }
}

void Application::run() {
  V6_PROFILE_FUNCTION();
  while (running) {
    V6_PROFILE_SCOPE("RunLoop")
    double time = glfwGetTime();
    Timestep timestep = time - lastFrameTimeSec;
    lastFrameTimeSec = time;

    if (!minimized) {
      {
        V6_PROFILE_SCOPE("LayerStack OnUpdates")
        for (Layer *layer : layerStack)
          layer->onUpdate(timestep.getSeconds());
      }
      imGuiLayer->begin();
      {
        V6_PROFILE_SCOPE("LayerStack onImGuiRender")
        for (Layer *layer : layerStack)
          layer->onImGuiRender();
      }
      imGuiLayer->end();
    }
    pWindow->OnUpdate();
  }
}

bool Application::onWindowClosed([[maybe_unused]] WindowCloseEvent &e) {
  running = false;
  return true;
}

bool Application::onWindowResize([[maybe_unused]] WindowResizeEvent &e) {
  V6_PROFILE_FUNCTION();
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
