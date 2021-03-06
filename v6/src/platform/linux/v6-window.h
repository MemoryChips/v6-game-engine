#pragma once

#include "platform/opengl/opengl-context.h"
#include "v6-pch.h"
#include "window.h"

#include "GLFW/glfw3.h"

namespace v6 {

class V6Window : public Window {
public:
  V6Window(const WindowProps &props);
  virtual ~V6Window();

  void OnUpdate() override;

  inline unsigned int GetWidth() const override { return m_Data.Width; }
  inline unsigned int GetHeight() const override { return m_Data.Height; }

  // Window attributes
  inline void SetEventCallback(const EventCallbackFn &callback) override {
    m_Data.EventCallback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  inline virtual void *GetNativeWindow() const { return m_Window; }

private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

private:
  GLFWwindow *m_Window;
  Scope<GraphicsContext> m_Context;
  // GraphicsContext *m_Context;

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
};

} // namespace v6
