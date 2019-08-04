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

  void UploadUniformInt(const std::string &name, const int &v);

  void UploadUniformFloat(const std::string &name, const float &v);
  void UploadUniformFloat2(const std::string &name, const glm::vec2 &v);
  void UploadUniformFloat3(const std::string &name, const glm::vec3 &v);
  void UploadUniformFloat4(const std::string &name, const glm::vec4 &v);

  void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
  void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
  uint32_t rendererId;
};

} // namespace v6
