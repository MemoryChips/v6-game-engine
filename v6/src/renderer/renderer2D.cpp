#include "renderer2D.h"
#include "v6-pch.h"

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
  std::dynamic_pointer_cast<OpenGLShader>(pData->pFlatColorShader)->bind();
  std::dynamic_pointer_cast<v6::OpenGLShader>(pData->pFlatColorShader)
      ->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
  std::dynamic_pointer_cast<v6::OpenGLShader>(pData->pFlatColorShader)
      ->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
}
void Renderer2D::endScene() {}

// Primitives
void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  std::dynamic_pointer_cast<OpenGLShader>(pData->pFlatColorShader)->bind();
  std::dynamic_pointer_cast<v6::OpenGLShader>(pData->pFlatColorShader)
      ->UploadUniformFloat4("u_Color", color);
  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

} // namespace v6