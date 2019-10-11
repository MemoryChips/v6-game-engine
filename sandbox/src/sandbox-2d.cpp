#include "sandbox-2d.h"
#include "events/event.h"
#include "imgui.h"
#include <gtc/type_ptr.hpp>

using namespace v6;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), orthoCamController(1280.0f / 720.0f) {}

void Sandbox2D::onDetach() {}

void Sandbox2D::onImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
  ImGui::End();
}

void Sandbox2D::onEvent(v6::Event &e) { orthoCamController.onEvent(e); }

void Sandbox2D::onAttach() {

  pSquareVA = VertexArray::Create();

  // clang-format off
  float squareVertices[3 * 4] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f,  0.0f,
    0.5f,  0.5f, 0.0f, 
    -0.5f, 0.5f, 0.0f
  };

  Ref<VertexBuffer> pSquareVB;
  // pSquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
  pSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  pSquareVB->SetLayout({
    { ShaderDataType::Float3, "a_Position" }
  });
  pSquareVA->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> pSquareIB;
  pSquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
  pFlatColorShader = v6::Shader::Create("sandbox/assets/shaders/flatColor.glsl");
  pSquareVA->SetIndexBuffer(pSquareIB);

}

void Sandbox2D::onUpdate(Timestep ts) {
  // Update
  orthoCamController.onUpdate(ts);

  // Render
  v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  v6::RenderCommand::Clear();

  v6::Renderer::BeginScene(orthoCamController.GetCamera());

  std::dynamic_pointer_cast<v6::OpenGLShader>(pFlatColorShader)->bind();
  std::dynamic_pointer_cast<v6::OpenGLShader>(pFlatColorShader)->UploadUniformFloat4("u_Color", squareColor);
  // pFlatColorShader->bind();
  // pFlatColorShader->UploadUniformFloat4("u_Color", squareColor);

  glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
  v6::Renderer::Submit(pFlatColorShader, pSquareVA, scale2);

  v6::Renderer::EndScene();
}

