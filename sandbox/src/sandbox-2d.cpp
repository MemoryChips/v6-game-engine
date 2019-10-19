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

void Sandbox2D::onAttach() {}

void Sandbox2D::onUpdate(Timestep ts) {
  // Update
  orthoCamController.onUpdate(ts);

  // Render
  v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  v6::RenderCommand::Clear();

  v6::Renderer2D::beginScene(orthoCamController.GetCamera());
  v6::Renderer2D::drawQuad({0.0f, 0.0f}, {1.0, 1.0f}, {0.8f, 0.1f, 0.1f, 1.0f});
  v6::Renderer2D::endScene();

  // TODO: Shader::setMat4 Shader::setFloat4
  // std::dynamic_pointer_cast<v6::OpenGLShader>(pFlatColorShader)->bind();
  // std::dynamic_pointer_cast<v6::OpenGLShader>(pFlatColorShader)->UploadUniformFloat4("u_Color",
  // squareColor);

  // glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
  // v6::Renderer::Submit(pFlatColorShader, pSquareVA, scale2);
}
