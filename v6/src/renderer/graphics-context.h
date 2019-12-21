#pragma once

#include "v6-pch.h"

namespace v6 {

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
  static Scope<GraphicsContext> Create(void *window);
};

} // namespace v6
