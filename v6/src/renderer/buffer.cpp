// #include "hzpch.h"
#include "renderer/buffer.h"
#include "core.h"
#include "log.h"
#include "platform/opengl/opengl-buffer.h"
#include "renderer/renderer.h"

namespace v6 {

VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLVertexBuffer(vertices, size);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLIndexBuffer(indices, size);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6