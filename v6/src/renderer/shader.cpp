#include "shader.h"
#include "platform/opengl/opengl-shader.h"
#include "renderer/renderer-api.h"

namespace v6 {

Shader *Shader::Create(const std::string &vertexSrc,
                       const std::string &fragmentSource) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return new OpenGLShader(vertexSrc, fragmentSource);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6
