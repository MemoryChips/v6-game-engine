#pragma once

#include <glm.hpp>

#include "vertex-array.h"

namespace v6 {

class RendererAPI {
public:
  enum class API { None = 0, OpenGL = 1 };

public:
  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

  inline static API GetAPI() { return s_API; }

private:
  static API s_API;
};

} // namespace v6