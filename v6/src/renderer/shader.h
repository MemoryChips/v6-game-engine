#pragma once

#include <glm.hpp>
#include <string>

namespace v6 {

class Shader {
public:
  Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
  uint32_t rendererId;
};

} // namespace v6