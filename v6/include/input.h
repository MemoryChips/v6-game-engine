#pragma once

#include "core.h"
#include "utility" // for std::pair

namespace v6 {
class Input {
private:
  static Input *sInstance;

protected:
  virtual bool isKeyPressedImpl(int keyCode) = 0;
  virtual bool isMouseButtonPressedImpl(int button) = 0;
  virtual std::pair<double, double> getMousePosImpl() = 0;
  virtual float getMouseXImpl() = 0;
  virtual float getMouseYImpl() = 0;
  Input() = default;

public:
  Input(const Input &) = delete;
  Input &operator=(const Input &) = delete;
  static inline bool isKeyPressed(int keyCode) {
    return sInstance->isKeyPressedImpl(keyCode);
  }
  static inline bool isMouseButtonPressed(int button) {
    return sInstance->isMouseButtonPressedImpl(button);
  }
  static inline std::pair<double, double> getMousePos() {
    return sInstance->getMousePosImpl();
  }
  static inline float getMouseX() { return sInstance->getMouseXImpl(); }
  static inline float getMouseY() { return sInstance->getMouseYImpl(); }
};
} // namespace v6
