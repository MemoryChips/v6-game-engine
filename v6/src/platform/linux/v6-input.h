#pragma once

#include "input.h"

namespace v6 {
class V6Input : public Input {
protected:
  virtual bool isKeyPressedImpl(int keyCode) override;
  virtual bool isMouseButtonPressedImpl(int button) override;
  virtual std::pair<double, double> getMousePosImpl() override;
  virtual float getMouseXImpl() override;
  virtual float getMouseYImpl() override;
};
} // namespace v6
