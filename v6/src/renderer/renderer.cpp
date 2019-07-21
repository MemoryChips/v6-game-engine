#include "renderer.h"

namespace v6 {
Renderer::SceneData *Renderer::spSceneData = new Renderer::SceneData;
void Renderer::BeginScene(OrthographicCamera &camera) {
  spSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertexArray,
                      const glm::mat4 &transform) {
  shader->Bind();
  shader->UploadUniformMat4("u_ViewProjection",
                            spSceneData->ViewProjectionMatrix);
  shader->UploadUniformMat4("u_Transform", transform);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

} // namespace v6
