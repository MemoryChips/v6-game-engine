#include "sandbox-2d.h"
#include "events/event.h"
#include "imgui.h"
#include <gtc/type_ptr.hpp>

using namespace v6;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), orthoCamController(1280.0f / 720.0f) {}

void Sandbox2D::onDetach() { V6_PROFILE_FUNCTION(); }

void Sandbox2D::onEvent(v6::Event &e) { orthoCamController.onEvent(e); }

void Sandbox2D::onAttach() {
  V6_PROFILE_FUNCTION();
  pCheckerboardTexture =
      Texture2D::create("./sandbox/assets/textures/checkerboard.png");
  pShowerPeterArnoTexture =
      Texture2D::create("./sandbox/assets/textures/shower-peter-arno.png");
}

void Sandbox2D::onUpdate(Timestep ts) {

  V6_PROFILE_FUNCTION();

  // Update
  {
    V6_PROFILE_SCOPE("CameraController::OnUpdate");
    orthoCamController.onUpdate(ts);
  }

  // Render
  {
    V6_PROFILE_SCOPE("Render Prep");
    v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    v6::RenderCommand::Clear();
  }
  {
    V6_PROFILE_SCOPE("Renderer Draw");
    v6::Renderer2D::beginScene(orthoCamController.GetCamera());
    v6::Renderer2D::drawRotatedQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
                                    glm::radians(22.5f),
                                    {0.8f, 0.1f, 0.1f, 1.0f});
    // v6::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
    //                          {0.8f, 0.1f, 0.1f, 1.0f});
    v6::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f},
                             {0.2f, 0.3f, 0.8f, 1.0f});
    v6::Renderer2D::drawRotatedQuad({0.2f, 0.5f, -0.1f}, {5.0f, 5.0f},
                                    3.14159f / 4.0F, pCheckerboardTexture,
                                    10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
    // v6::Renderer2D::drawQuad({0.2f, 0.5f, -0.1f}, {5.0f, 5.0f},
    //                          pCheckerboardTexture, 10.0f,
    //                          glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
    // v6::Renderer2D::drawQuad({0.0f, 0.5f}, {0.8f, 0.8f},
    //                          pShowerPeterArnoTexture);
    v6::Renderer2D::endScene();
  }
}

void Sandbox2D::onImGuiRender() {

  V6_PROFILE_FUNCTION();

  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));

  ImGui::End();
}
