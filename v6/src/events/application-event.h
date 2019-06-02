#pragma once

#include "event.h"

namespace v6 {

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : m_Width(width), m_Height(height) {}

  inline unsigned int GetWidth() const { return m_Width; }
  inline unsigned int GetHeight() const { return m_Height; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return ss.str();
  }

  static EventType GetStaticType() { return EventType::WindowResize; }
  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
  unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() {}

  static EventType GetStaticType() { return EventType::WindowClose; }
  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event {
public:
  AppTickEvent() {}

  static EventType GetStaticType() { return EventType::AppTick; }
  EVENT_CLASS_TYPE(AppTick)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
  AppUpdateEvent() {}

  static EventType GetStaticType() { return EventType::AppUpdate; }
  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
public:
  AppRenderEvent() {}

  static EventType GetStaticType() { return EventType::AppRender; }
  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
} // namespace v6
