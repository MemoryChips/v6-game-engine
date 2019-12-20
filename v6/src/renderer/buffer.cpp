// #include "hzpch.h"
#include "renderer/buffer.h"
#include "core.h"
#include "log.h"
#include "platform/opengl/opengl-buffer.h"
#include "renderer/renderer-api.h"

namespace v6 {

Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    // return new OpenGLVertexBuffer(vertices, size);
    return CreateRef<OpenGLVertexBuffer>(vertices, size);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t size) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateRef<OpenGLIndexBuffer>(indices, size);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6