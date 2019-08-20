#pragma once
#include "core.h"
#include <string>

namespace v6 {

class Texture {
public:
  virtual ~Texture() = default;
  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;
  virtual void bind(uint32_t slot = 0) const = 0;
};

class Texture2D : public Texture {
public:
  static Ref<Texture2D> create(const std::string &path);
};

} // namespace v6
