#include "platform/opengl/opengl-context.h"
#include "core.h"
#include "log.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
// #include <GL/GL.h>

namespace v6 {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {
  V6_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  V6_ASSERT(status, "Failed to initialize Glad!");
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace v6