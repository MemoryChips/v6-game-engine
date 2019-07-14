#pragma once

#include "renderer/renderer-api.h"

namespace v6 {
class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;
  virtual void
  DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};
} // namespace v6
