#pragma once
#include "string"

namespace v6 {

class Shader {
public:
  virtual ~Shader() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  static Shader *Create(const std::string &vertexSrc,
                        const std::string &framentSource);
  static Shader *Create(const std::string &filePath);
};

} // namespace v6