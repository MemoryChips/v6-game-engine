#include "renderer2D.h"
#include "v6-pch.h"
#include <gtc/matrix_transform.hpp>

namespace v6 {

struct R2DStorage {
  Ref<VertexArray> pQuadVeretexArray;
  Ref<Shader> pTextureShader;
  Ref<Texture2D> pWhiteTexture;
};

static R2DStorage *pData;

void Renderer2D::init() {

  V6_PROFILE_FUNCTION();

  pData = new R2DStorage();
  pData->pQuadVeretexArray = VertexArray::Create();

  // clang-format off
  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
  };
  // clang-format on

  Ref<VertexBuffer> pSquareVB;

  pSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  pSquareVB->SetLayout({{ShaderDataType::Float3, "a_Position"},
                        {ShaderDataType::Float2, "a_TexCoord"}});
  pData->pQuadVeretexArray->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> pSquareIB;
  pSquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                         sizeof(uint32_t)));
  pData->pQuadVeretexArray->SetIndexBuffer(pSquareIB);

  pData->pWhiteTexture = Texture2D::create(1, 1);
  uint32_t whiteTextureData = 0xffffffff;
  pData->pWhiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

  pData->pTextureShader = Shader::Create("sandbox/assets/shaders/texture.glsl");
  pData->pTextureShader->bind();
  pData->pTextureShader->setInt("u_Texture", 0);
}

void Renderer2D::shutdown() { delete pData; }

void Renderer2D::beginScene(const OrthographicCamera &camera) {

  pData->pTextureShader->bind();
  pData->pTextureShader->setMat4("u_ViewProjection",
                                 camera.GetViewProjectionMatrix());
}

void Renderer2D::endScene() {}

// Primitives
void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  pData->pTextureShader->setFloat4("u_Color", color);
  pData->pWhiteTexture->bind();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) * /* rotation here */
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);

  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const Ref<Texture2D> texture) {
  drawQuad({position.x, position.y, 0.0f}, size, texture);
}
void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const Ref<Texture2D> texture) {
  // pData->pTextureShader->setFloat4("u_Color", {0.2f, 0.3f, 0.8f, 0.5f});
  pData->pTextureShader->setFloat4("u_Color", glm::vec4(1.0f));
  texture->bind();
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) * /* rotation here */
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);
  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

} // namespace v6