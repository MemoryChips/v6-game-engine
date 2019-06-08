#pragma once

namespace v6 {

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

} // namespace v6
