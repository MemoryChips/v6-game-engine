#pragma once
#include "imgui.h"
#include "memory"
#include "v6-pch.h"
#include <gtc/type_ptr.hpp>

using namespace v6;

class ExampleLayer : public Layer {
public:
  ExampleLayer();
  ~ExampleLayer() = default;
  void onAttach() override;
  void onDetach() override;
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
  Ref<Texture2D> pTexture, pChernoLogoTexture, pShowerPeterArnoTexture;
  OrthoCamController orthoCamController;
  // OrthographicCamera camera;
  // glm::vec3 cameraPosition;
  // float cameraRotation;
  // float cameraSpeed;
  // float cameraRotationSpeed;

  glm::vec3 squareColor = {0.2f, 0.3f, 0.8f};

  // glm::vec3 squarePosition;
};
