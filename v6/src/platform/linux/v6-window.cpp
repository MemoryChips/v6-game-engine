#include "platform/linux/v6-window.h"
#include "events/application-event.h"
#include "events/key-event.h"
#include "events/mouse-event.h"
#include "log.h"
#include "platform/opengl/opengl-context.h"

// #include "glad.h"

namespace v6 {

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char *description) {
  LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
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

  if (!s_GLFWWindowCount) {
    LOG_CORE_INFO("Initializing GLFW");
    int success = glfwInit();
    V6_CORE_ASSERT(success, "Could not intialize GLFW!");
    // Enable glfw error callback
    glfwSetErrorCallback(GLFWErrorCallback);
    ++s_GLFWWindowCount;
  }

  m_Window = glfwCreateWindow((int)props.width, (int)props.height,
                              m_Data.Title.c_str(), nullptr, nullptr);

  m_Context = new OpenGLContext(m_Window);
  m_Context->Init();

  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        // LOG_CORE_WARN("{0}, {1}", width, height);
        data.EventCallback(event);
      });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key,
                                  [[maybe_unused]] int scancode, int action,
                                  [[maybe_unused]] int mods) {
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
      KeyPressedEvent event(key, 1); // get repeat count from glfw?
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

  glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button,
                                          int action,
                                          [[maybe_unused]] int mods) {
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

void V6Window::Shutdown() {
  glfwDestroyWindow(m_Window);
  if (--s_GLFWWindowCount == 0) {
    LOG_CORE_INFO("Terminating GLFW");
    glfwTerminate();
  }
}

void V6Window::OnUpdate() {
  glfwPollEvents();
  m_Context->SwapBuffers();
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
