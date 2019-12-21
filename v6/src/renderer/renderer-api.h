#pragma once

#include <glm.hpp>

#include "vertex-array.h"

namespace v6 {

class RendererAPI {
public:
  enum class API { None = 0, OpenGL = 1, OpenGL3 = 2 };

public:
  virtual void init() = 0;
  virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void Clear() = 0;
  virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) = 0;
  inline static API GetAPI() { return s_API; }
  static Scope<RendererAPI> Create();

private:
  static API s_API;
};

} // namespace v6