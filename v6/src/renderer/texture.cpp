#include "texture.h"
#include "log.h"
#include "platform/opengl/opengl-texture.h"
#include "renderer.h"

namespace v6 {

Ref<Texture2D> Texture2D::create(const std::string &path) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLTexture2D>(path);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
} // namespace v6
