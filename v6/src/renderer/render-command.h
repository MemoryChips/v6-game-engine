#pragma once

#include "renderer-api.h"

namespace v6 {

class RenderCommand {
public:
  inline static void init() { s_RendererAPI->init(); }
  inline static void SetViewport(uint32_t x, uint32_t y, uint32_t w,
                                 uint32_t h) {
    s_RendererAPI->SetViewport(x, y, w, h);
  };
  inline static void SetClearColor(const glm::vec4 &color) {
    s_RendererAPI->SetClearColor(color);
  }

  inline static void Clear() { s_RendererAPI->Clear(); }

  inline static void DrawIndexed(const Ref<VertexArray> &vertexArray) {
    s_RendererAPI->DrawIndexed(vertexArray);
  }

private:
  static RendererAPI *s_RendererAPI;
};

} // namespace v6
