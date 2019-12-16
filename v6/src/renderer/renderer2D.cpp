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

void Renderer2D::shutdown() {
  V6_PROFILE_FUNCTION();
  delete pData;
}

void Renderer2D::beginScene(const OrthographicCamera &camera) {
  V6_PROFILE_FUNCTION();

  pData->pTextureShader->bind();
  pData->pTextureShader->setMat4("u_ViewProjection",
                                 camera.GetViewProjectionMatrix());
}

void Renderer2D::endScene() { V6_PROFILE_FUNCTION(); }

// Primitives
void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  drawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const glm::vec4 color) {
  V6_PROFILE_FUNCTION();
  pData->pTextureShader->setFloat4("u_Color", color);
  pData->pTextureShader->setFloat("u_TilingFactor", 1.0);
  pData->pWhiteTexture->bind();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) * /* rotation here */
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);

  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                          const Ref<Texture2D> texture,
                          const float tilingFactor) {
  drawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor);
}
void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                          const Ref<Texture2D> texture,
                          const float tilingFactor) {
  V6_PROFILE_FUNCTION();
  pData->pTextureShader->setFloat4("u_Color", glm::vec4(1.0f));
  pData->pTextureShader->setFloat("u_TilingFactor", tilingFactor);
  texture->bind();
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                        glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);
  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2 &position,
                                 const glm::vec2 &size,
                                 const float &rotationRadians,
                                 const glm::vec4 color) {
  drawRotatedQuad({position.x, position.y, 0.0f}, size, rotationRadians, color);
}

void Renderer2D::drawRotatedQuad(const glm::vec3 &position,
                                 const glm::vec2 &size,
                                 const float &rotationRadians,
                                 const glm::vec4 color) {
  V6_PROFILE_FUNCTION();
  pData->pTextureShader->setFloat4("u_Color", color);
  pData->pTextureShader->setFloat("u_TilingFactor", 1.0);
  pData->pWhiteTexture->bind();

  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) *
      glm::rotate(glm::mat4(1.0f), rotationRadians, {0.0f, 0.0f, 1.0f}) *
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);

  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

void Renderer2D::drawRotatedQuad(const glm::vec2 &position,
                                 const glm::vec2 &size,
                                 const float &rotationRadians,
                                 const Ref<Texture2D> texture,
                                 const float tilingFactor) {
  drawRotatedQuad({position.x, position.y, 0.0f}, size, rotationRadians,
                  texture, tilingFactor);
}
void Renderer2D::drawRotatedQuad(const glm::vec3 &position,
                                 const glm::vec2 &size,
                                 const float &rotationRadians,
                                 const Ref<Texture2D> texture,
                                 const float tilingFactor) {
  V6_PROFILE_FUNCTION();
  pData->pTextureShader->setFloat4("u_Color", glm::vec4(1.0f));
  pData->pTextureShader->setFloat("u_TilingFactor", tilingFactor);
  texture->bind();
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position) *
      glm::rotate(glm::mat4(1.0f), rotationRadians, {0.0f, 0.0f, 1.0f}) *
      glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
  pData->pTextureShader->setMat4("u_Transform", transform);
  pData->pQuadVeretexArray->Bind();
  RenderCommand::DrawIndexed(pData->pQuadVeretexArray);
}

} // namespace v6