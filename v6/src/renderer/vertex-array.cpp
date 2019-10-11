// #include "hzpch.h"
#include "vertex-array.h"
#include "log.h"
#include "platform/opengl/opengl-vertex-array.h"
#include "renderer-api.h"

namespace v6 {

Ref<VertexArray> VertexArray::Create() {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLVertexArray>();
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6