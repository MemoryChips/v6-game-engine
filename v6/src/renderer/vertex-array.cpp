// #include "hzpch.h"
#include "vertex-array.h"
#include "log.h"
#include "platform/opengl/opengl-vertex-array.h"
#include "renderer-api.h"

namespace v6 {

VertexArray *VertexArray::Create() {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return new OpenGLVertexArray();
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6