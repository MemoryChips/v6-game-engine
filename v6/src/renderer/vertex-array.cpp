// #include "hzpch.h"
#include "vertex-array.h"
#include "log.h"
#include "platform/opengl/opengl-vertex-array.h"
#include "renderer.h"

namespace v6 {

VertexArray *VertexArray::Create() {
  switch (Renderer::GetAPI()) {
  case RendererAPI::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLVertexArray();
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6