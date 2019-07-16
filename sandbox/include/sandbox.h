#pragma once

#include "imgui.h"
#include "v6.h"

class ExampleLayer : public v6::Layer {
public:
  ExampleLayer();
  void onUpdate() override;
  virtual void onImGuiRender() override;
  void onEvent(v6::Event &e) override;

private:
  std::shared_ptr<v6::Shader> pShader;
  std::shared_ptr<v6::VertexArray> pVertexArray;
  std::shared_ptr<v6::Shader> pBlueShader;
  std::shared_ptr<v6::VertexArray> pSquareVA;
  v6::OrthographicCamera camera;
};

class Sandbox : public v6::Application {
public:
  Sandbox(/* args */);
  ~Sandbox();
};
