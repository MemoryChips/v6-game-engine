#pragma once

#include "renderer/graphics-context.h"

struct GLFWwindow;

namespace v6 {

class OpenGLContext : public GraphicsContext {
public:
  OpenGLContext(GLFWwindow *windowHandle);

  virtual void Init() override;
  virtual void SwapBuffers() override;

private:
  GLFWwindow *m_WindowHandle;
};

} // namespace v6
