#pragma once

#include "orthographic-camera.h"
#include "texture.h"

namespace v6 {
class Renderer2D {
public:
  static void init();
  static void shutdown();

  static void beginScene(const OrthographicCamera &camera);
  static void endScene();

  // Primitives
  static void drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const glm::vec4 color);
  static void drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const glm::vec4 color);
  static void drawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const Ref<Texture2D> texture);
  static void drawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const Ref<Texture2D> texture);
};

} // namespace v6