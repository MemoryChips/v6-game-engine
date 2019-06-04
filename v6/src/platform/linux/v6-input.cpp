// #include "input.h"
#include "platform/linux/v6-input.h"
#include "GLFW/glfw3.h"
#include "application.h"
#include "v6-pch.h"

#define GET_WINDOW                                                             \
  static_cast<GLFWwindow *>(Application::get().getWindow().GetNativeWindow())

namespace v6 {

Input *Input::sInstance = new V6Input();

bool V6Input::isKeyPressedImpl(int keyCode) {
  auto window = GET_WINDOW;
  auto state = glfwGetKey(window, keyCode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool V6Input::isMouseButtonPressedImpl(int button) {
  auto window = GET_WINDOW;
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<double, double> V6Input::getMousePosImpl() {
  auto window = GET_WINDOW;
  std::pair<double, double> pos;
  glfwGetCursorPos(window, &pos.first, &pos.second);
  return pos;
};

float V6Input::getMouseXImpl() {
  return (float)(getMousePosImpl().first);
  // auto [x, _y] = getMousePosImpl();
  // return (float)x;
}
float V6Input::getMouseYImpl() {
  return (float)(getMousePosImpl().second);
  // auto [_x, y] = getMousePosImpl();
  // return (float)y;
}

} // namespace v6
