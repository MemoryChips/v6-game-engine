#pragma once
#include "renderer/orthographic-camera.h"
#include "renderer/render-command.h"
#include "shader.h"

namespace v6 {

class Renderer {
public:
  static void BeginScene(OrthographicCamera &camera);
  static void EndScene();
  static void Submit(const std::shared_ptr<Shader> &shader,
                     const std::shared_ptr<VertexArray> &vertexArray,
                     const glm::mat4 &transform = glm::mat4(1.0f));

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static SceneData *spSceneData;
};
} // namespace v6