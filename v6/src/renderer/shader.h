#pragma once

#include <string>

namespace v6 {

class Shader {
public:
  Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
  ~Shader();

  void Bind() const;
  void Unbind() const;

private:
  uint32_t rendererId;
};

} // namespace v6