#include "renderer2D.h"
#include "v6-pch.h"
#include <gtc/matrix_transform.hpp>

namespace v6 {

struct R2DStorage {
  Ref<VertexArray> pQuadVeretexArray;
  Ref<Shader> pFlatColorShader;
};

static R2DStorage *pData;

void Renderer2D::init() {

  pData = new R2DStorage();
  pData->pQuadVeretexArray = VertexArray::Create();

  // clang-format off
  float squareVertices[3 * 4] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f
  };
  // clang-format on

  Ref<VertexBuffer> pSquareVB;
  // pSquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
  pSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  pSquareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
  pData->pQuadVeretexArray->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> pSquareIB;
  pSquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                         sizeof(uint32_t)));
  pData->pQuadVeretexArray->SetIndexBuffer(pSquareIB);
  pData->pFlatColorShader =
      Shader::Create("sandbox/assets/shaders/flatColor.glsl");
}

void Renderer2D::shutdown() { delete pData; }

void Renderer2D::beginScene(const OrthographicCamera &camera) {
  pData->pFlatColorShader->bind();
  pData->pFlatColorShader->setMat4("u_ViewProjection",
                                   camera.GetViewProjectionMatrix());
  // pData->pFlatColorShader->setMat4("u_Transform", glm::mat4(1.0f));
}

void Renderer2D::endScene() {}

// Primitives
void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  pData->pFlatColorShader->bind();
  pData->pFlatColorShader->setFloat4("u_Color", color);

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) * /* rotation here */
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pFlatColorShader->setMat4("u_Transform", transform);

  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

} // namespace v6