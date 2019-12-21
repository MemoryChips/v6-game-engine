#include "shader.h"
#include "platform/opengl/opengl-shader.h"
#include "renderer/renderer-api.h"

namespace v6 {

void ShaderLibrary::add(const Ref<Shader> &pShader) {
  auto &name = pShader->getName();
  add(name, pShader);
}
void ShaderLibrary::add(const std::string name, const Ref<Shader> &pShader) {
  V6_CORE_ASSERT(!exists(name), "Shader Name duplicated")
  mShaders[name] = pShader;
}
Ref<Shader> ShaderLibrary::load(const std::string &filePath) {
  auto shader = Shader::Create(filePath);
  add(shader);
  return shader;
}
Ref<Shader> ShaderLibrary::load(const std::string &name,
                                const std::string &filePath) {
  auto shader = Shader::Create(filePath);
  add(name, shader);
  return shader;
}
Ref<Shader> ShaderLibrary::get(const std::string &name) {
  V6_CORE_ASSERT(exists(name), "Shader Name not found")
  return mShaders[name];
}
bool ShaderLibrary::exists(const std::string &name) const {
  return mShaders.find(name) != mShaders.end();
}
Ref<Shader> Shader::Create(const std::string &filePath) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateRef<OpenGLShader>(filePath);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<Shader> Shader::Create(const std::string &name,
                           const std::string &vertexSrc,
                           const std::string &fragmentSource) {
  switch (RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    V6_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL3:
    V6_CORE_ASSERT(false, "RendererAPI::OpenGL3 is currently not supported!");
    return nullptr;
  case RendererAPI::API::OpenGL:
    return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSource);
  }

  V6_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

} // namespace v6
