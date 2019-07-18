#pragma once

#include "imgui.h"
#include "v6.h"

using namespace v6;

class ExampleLayer : public Layer {
public:
  ExampleLayer();
  void onUpdate(double tsSec) override;
  virtual void onImGuiRender() override;
  void onEvent(Event &e) override;
  bool onKeyPressedEvent(KeyPressedEvent &e);

private:
  std::shared_ptr<v6::Shader> pShader;
  std::shared_ptr<v6::VertexArray> pVertexArray;
  std::shared_ptr<v6::Shader> pBlueShader;
  std::shared_ptr<v6::VertexArray> pSquareVA;
  OrthographicCamera camera;
  glm::vec3 cameraPosition;
  float cameraRotation;
  float cameraSpeed;
  float cameraRotationSpeed;
};

class Sandbox : public Application {
public:
  Sandbox(/* args */);
  ~Sandbox();
};
