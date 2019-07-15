#include "renderer.h"

namespace v6 {
Renderer::SceneData *Renderer::spSceneData = new Renderer::SceneData;
void Renderer::BeginScene(OrthographicCamera &camera) {
  spSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertexArray) {
  shader->Bind();
  shader->UploadUniformMat4("u_ViewProjection",
                            spSceneData->ViewProjectionMatrix);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

} // namespace v6
