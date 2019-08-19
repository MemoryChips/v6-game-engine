#pragma once

#include "imgui.h"
#include "v6.h"
#include <gtc/matrix_transform.hpp>

using namespace v6;

class ExampleLayer : public Layer {
public:
  ExampleLayer();
  void onUpdate(double tsSec) override;
  virtual void onImGuiRender() override;
  void onEvent(Event &e) override;
  bool onKeyPressedEvent(KeyPressedEvent &e);

private:
  Ref<v6::Shader> pShader;
  Ref<v6::VertexArray> pVertexArray;
  Ref<v6::Shader> pFlatColorShader, pTextureShader;
  Ref<v6::VertexArray> pSquareVA;
  OrthographicCamera camera;
  glm::vec3 cameraPosition;
  float cameraRotation;
  float cameraSpeed;
  float cameraRotationSpeed;

  glm::vec3 squareColor;

  glm::vec3 squarePosition;
};

class Sandbox : public Application {
public:
  Sandbox(/* args */);
  ~Sandbox();
};
