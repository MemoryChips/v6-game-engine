#pragma once

#include "renderer/renderer-api.h"

namespace v6 {
class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void init() override;
  virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w,
                           uint32_t h) override;
  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;
  virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
};
} // namespace v6
