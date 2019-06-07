#pragma once

#include "v6.h"

class ExampleLayer : public v6::Layer {
public:
  ExampleLayer() : Layer("Example") {}
  void onUpdate() override {
    count++;
    if (count > 5000) {
      count = 0;
      LOG_INFO("ExampleLayer::Update");
    }
    if (v6::Input::isKeyPressed(V6_KEY_TAB))
      LOG_TRACE("Tab key pressed (poll)!");
  }
  void onEvent(v6::Event &e) override {
    // a comment
    if (e.GetEventType() == v6::EventType::MouseMoved) {
      mouseMovedCount++;
      if (mouseMovedCount > 500) {
        mouseMovedCount = 0;
        LOG_TRACE("{0}", e);
      }
    }
    if (e.GetEventType() == v6::EventType::KeyPressed) {
      auto keyEvent = (v6::KeyPressedEvent &)e;
      if (keyEvent.GetKeyCode() == V6_KEY_TAB) {
        LOG_TRACE("Tab key pressed (event)!");
      }
      // LOG_TRACE("{0}", e);
    }
  }

private:
  int count = 0;
  int mouseMovedCount = 0;
};

class Sandbox : public v6::Application {
private:
  /* data */
public:
  Sandbox(/* args */) { pushLayer(new ExampleLayer()); }
  ~Sandbox();
};

Sandbox::~Sandbox() {}
