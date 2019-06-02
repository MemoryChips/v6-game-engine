#pragma once

#include "v6-pch.h"
// #include "v6.h"

#include "core.h"
#include "events/event.h"

namespace v6 {

struct WindowProps {
  std::string title;
  unsigned int width;
  unsigned int height;

  WindowProps(const std::string &title = "V6 Engine", unsigned int width = 1280,
              unsigned int height = 720)
      : title(title), width(width), height(height) {}
};

// Interface representing a desktop system based Window
class Window {
public:
  using EventCallbackFn = std::function<void(Event &)>;

  virtual ~Window() {}

  virtual void OnUpdate() = 0;

  virtual unsigned int GetWidth() const = 0;
  virtual unsigned int GetHeight() const = 0;

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  virtual void *GetNativeWindow() const = 0;

  static Window *Create(const WindowProps &props = WindowProps());
};

} // namespace v6
