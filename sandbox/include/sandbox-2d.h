#pragma once

#include "v6-pch.h"

#include "imgui.h"
#include <gtc/matrix_transform.hpp>

using namespace v6;

class Sandbox2D : public v6::Layer {
public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;
  virtual void onAttach() override;
  virtual void onDetach() override;
  void onUpdate(Timestep ts) override;
  virtual void onImGuiRender() override;
  void onEvent(Event &e) override;

private:
  OrthoCamController orthoCamController;

  // Temp
  Ref<VertexArray> pSquareVA;
  Ref<Shader> pFlatColorShader;
  // Ref<Shader> pShader;

  glm::vec4 squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};