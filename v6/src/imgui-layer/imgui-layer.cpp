#include "imgui-layer/imgui-layer.h"
#include "v6-pch.h"

#include "imgui.h"
#include "platform/opengl/imgui-opengl-renderer.h"

#include "application.h"

// TEMPORARY
#include "glad/glad.h"
#include "glfw3.h" // temporary?

namespace v6 {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::onAttach() {
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  // TEMPORARY: should eventually use v6 key codes
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::onDetach() {}

void ImGuiLayer::onUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  auto &window = Application::get().getWindow();
  io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());
  // Application &app = Application::get();
  // io.DisplaySize =
  //     ImVec2(app.getWindow().GetWidth(), app.getWindow().GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
  m_Time = time;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<MouseButtonPressedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
  dispatcher.Dispatch<MouseButtonReleasedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
  dispatcher.Dispatch<MouseMovedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
  dispatcher.Dispatch<MouseScrolledEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
  dispatcher.Dispatch<KeyPressedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
  dispatcher.Dispatch<KeyTypedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
  dispatcher.Dispatch<KeyReleasedEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
  dispatcher.Dispatch<WindowResizeEvent>(
      V6_BIND_EVENT_FN(ImGuiLayer::onWindowResizeEvent));
}

bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = true;

  return false;
}

bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = false;

  return false;
}

bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(e.GetX(), e.GetY());

  return false;
}

bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseWheelH += e.GetXOffset();
  io.MouseWheel += e.GetYOffset();

  return false;
}

bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = true;

  io.KeyCtrl =
      io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift =
      io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
  io.KeySuper =
      io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
  return false;
}

bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = false;

  return false;
}

bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  int keycode = e.GetKeyCode();
  if (keycode > 0 && keycode < 0x10000)
    io.AddInputCharacter((unsigned short)keycode);

  return false;
}

bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, e.GetWidth(), e.GetHeight());

  return false;
}

} // namespace v6
