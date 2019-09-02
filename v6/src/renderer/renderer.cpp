#include "renderer.h"

// temp work around for submit
#include "memory"
#include "platform/opengl/opengl-shader.h"

namespace v6 {
Renderer::SceneData *Renderer::spSceneData = new Renderer::SceneData;
void Renderer::init() { RenderCommand::init(); }
void Renderer::BeginScene(OrthographicCamera &camera) {
  spSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader> &shader,
                      const Ref<VertexArray> &vertexArray,
                      const glm::mat4 &transform) {
  shader->bind();

  // temp work around for now
  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
      "u_ViewProjection", spSceneData->ViewProjectionMatrix);
  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
      "u_Transform", transform);

  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

} // namespace v6
