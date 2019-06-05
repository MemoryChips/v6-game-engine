#include "v6-pch.h"

#include "log.h"
#include "platform/linux/v6-window.h"

#include "events/application-event.h"
#include "events/key-event.h"
#include "events/mouse-event.h"

// #include "glad.h"

namespace v6 {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
  LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

static void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id,
                                       GLenum severity, GLsizei length,
                                       const GLchar *message,
                                       const void *userParam) {
  if (type != 0x8251) {
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
  }
}

Window *Window::Create(const WindowProps &props) { return new V6Window(props); }

V6Window::V6Window(const WindowProps &props) { Init(props); }

V6Window::~V6Window() { Shutdown(); }

void V6Window::Init(const WindowProps &props) {
  m_Data.Title = props.title;
  m_Data.Width = props.width;
  m_Data.Height = props.height;

  LOG_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
                props.height);

  if (!s_GLFWInitialized) {
    // TODO: glfwTerminate on system shutdown
    int success = glfwInit();
    V6_CORE_ASSERT(success, "Could not intialize GLFW!");
    glfwSetErrorCallback(GLFWErrorCallback);
    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow((int)props.width, (int)props.height,
                              m_Data.Title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  V6_CORE_ASSERT(status, "Failed to initialize Glad!");
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Enable debugging with new fancy callback
  // requires 4.0 or above
  // This must be called after we create a context or something like that
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(messageCallback, nullptr);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(key, 0);
      data.EventCallback(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      data.EventCallback(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(key, 1);
      data.EventCallback(event);
      break;
    }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    KeyTypedEvent event(keycode);
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
}

void V6Window::Shutdown() { glfwDestroyWindow(m_Window); }

void V6Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void V6Window::SetVSync(bool enabled) {
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool V6Window::IsVSync() const { return m_Data.VSync; }

} // namespace v6
