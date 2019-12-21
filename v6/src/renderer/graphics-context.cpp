#include "renderer/graphics-context.h"

#include "platform/opengl/opengl-context.h"
#include "renderer/renderer.h"

namespace v6 {

Scope<GraphicsContext> GraphicsContext::Create(void *window) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6