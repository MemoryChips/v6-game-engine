#pragma once

#include "renderer/shader.h"
#include <glm.hpp>
#include <string>

namespace v6 {

class OpenGLShader : public Shader {
public:
  OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
  ~OpenGLShader();

  virtual void bind() const override;
  virtual void unbind() const override;

  void UploadUniformFloat4(const std::string &name, const glm::vec4 &v);
  void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
  uint32_t rendererId;
};

} // namespace v6
