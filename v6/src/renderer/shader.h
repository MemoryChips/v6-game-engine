#pragma once
#include "core.h"
#include <string>
#include <unordered_map>

#include <glm.hpp>

namespace v6 {

class Shader {
public:
  virtual ~Shader() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual void setInt(const std::string &name, int value) = 0;
  virtual void setFloat3(const std::string &name, const glm::vec3 &f) = 0;
  virtual void setFloat4(const std::string &name, const glm::vec4 &f) = 0;
  virtual void setMat4(const std::string &name, const glm::mat4 &m) = 0;

  virtual const std::string &getName() const = 0;
  static Ref<Shader> Create(const std::string &name,
                            const std::string &vertexSrc,
                            const std::string &framentSource);
  static Ref<Shader> Create(const std::string &filePath);
};

class ShaderLibrary {
public:
  void add(const Ref<Shader> &s);
  void add(const std::string name, const Ref<Shader> &s);
  Ref<Shader> load(const std::string &filePath);
  Ref<Shader> load(const std::string &name, const std::string &filePath);
  Ref<Shader> get(const std::string &name);
  bool exists(const std::string &name) const;

private:
  std::unordered_map<std::string, Ref<Shader>> mShaders;
};

} // namespace v6