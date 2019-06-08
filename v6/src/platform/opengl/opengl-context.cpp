#include "platform/opengl/opengl-context.h"
#include "core.h"
#include "log.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
// #include <GL/GL.h>

namespace v6 {

static void GLAPIENTRY messageCallback([[maybe_unused]] GLenum source,
                                       GLenum type, [[maybe_unused]] GLuint id,
                                       GLenum severity,
                                       [[maybe_unused]] GLsizei length,
                                       const GLchar *message,
                                       [[maybe_unused]] const void *userParam) {
  if (type != 0x8251) {
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
  }
}

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {
  V6_ASSERT(windowHandle, "Window handle is null!");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  V6_ASSERT(status, "Failed to initialize Glad!");

#ifdef V6_DEBUG
  // Enable opengl debugging with new fancy callback
  // requires 4.0 or above
  // This must be called after we create a context or something like that
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(messageCallback, nullptr);
#endif

  LOG_CORE_INFO("OpenGL Info:");
  LOG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
  LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  LOG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace v6