#pragma once

#include "core/timestep.h"
#include "imgui.h"
#include "v6.h"
#include <gtc/matrix_transform.hpp>

using namespace v6;

class ExampleLayer : public Layer {
public:
  ExampleLayer();
  void onUpdate(Timestep ts) override;
  virtual void onImGuiRender() override;
  void onEvent(Event &e) override;
  bool onKeyPressedEvent(KeyPressedEvent &e);

private:
  ShaderLibrary shaderLibrary;
  Ref<Shader> pShader;
  Ref<VertexArray> pVertexArray;
  Ref<Shader> pFlatColorShader;
  // Ref<Shader> pFlatColorShader, pTextureShader;
  Ref<VertexArray> pSquareVA;
  Ref<Texture2D> pTexture, pChernoLogoTexture;
  OrthoCamController orthoCamController;
  // OrthographicCamera camera;
  // glm::vec3 cameraPosition;
  // float cameraRotation;
  // float cameraSpeed;
  // float cameraRotationSpeed;

  glm::vec3 squareColor = {0.2f, 0.3f, 0.8f};

  // glm::vec3 squarePosition;
};

class Sandbox : public Application {
public:
  Sandbox(/* args */);
  ~Sandbox();
};
