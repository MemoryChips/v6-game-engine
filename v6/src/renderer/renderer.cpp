#include "renderer.h"

namespace v6 {
void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

} // namespace v6
