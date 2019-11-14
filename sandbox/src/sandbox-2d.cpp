#include "sandbox-2d.h"
#include "events/event.h"
#include "imgui.h"
#include <gtc/type_ptr.hpp>

#include "timer.h"

using namespace v6;

#define PROFILE_SCOPE(name)                                                    \
  Timer timer##__LINE__(name, [&](ProfileResult profileResult) {               \
    profileResults.push_back(profileResult);                                   \
  })

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), orthoCamController(1280.0f / 720.0f) {}

void Sandbox2D::onDetach() {}

void Sandbox2D::onEvent(v6::Event &e) { orthoCamController.onEvent(e); }

void Sandbox2D::onAttach() {
  pCheckerboardTexture =
      Texture2D::create("./sandbox/assets/textures/checkerboard.png");
  pShowerPeterArnoTexture =
      Texture2D::create("./sandbox/assets/textures/shower-peter-arno.png");
}

void Sandbox2D::onUpdate(Timestep ts) {

  PROFILE_SCOPE("Sandbox2D::onUpdate");

  // Update
  {
    PROFILE_SCOPE("CameraController::OnUpdate");
    orthoCamController.onUpdate(ts);
  }

  // Render
  {
    PROFILE_SCOPE("Render Prep");
    v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    v6::RenderCommand::Clear();
  }
  {
    PROFILE_SCOPE("Renderer Draw");
    v6::Renderer2D::beginScene(orthoCamController.GetCamera());
    v6::Renderer2D::drawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
                             {0.8f, 0.1f, 0.1f, 1.0f});
    v6::Renderer2D::drawQuad({0.5f, -0.5f}, {0.5f, 0.75f},
                             {0.2f, 0.3f, 0.8f, 1.0f});
    v6::Renderer2D::drawQuad({0.2f, 0.5f, -0.1f}, {5.0f, 5.0f},
                             pCheckerboardTexture);
    // v6::Renderer2D::drawQuad({0.0f, 0.5f}, {0.8f, 0.8f},
    //                          pShowerPeterArnoTexture); // Fails. Too big?
    v6::Renderer2D::endScene();
  }
}

void Sandbox2D::onImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));

  for (auto &result : profileResults) {
    char label[50];
    strcpy(label, " %.3f mS");
    strcat(label, result.name);
    ImGui::Text(label, result.time);
  }
  profileResults.clear();

  ImGui::End();
}
