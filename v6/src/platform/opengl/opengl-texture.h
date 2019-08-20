#pragma once

#include "renderer/texture.h"

namespace v6 {
class OpenGLTexture2D : public Texture2D {
private:
  uint32_t width, height;
  uint32_t rendererId;
  std::string path;

public:
  OpenGLTexture2D(const std::string &path);
  ~OpenGLTexture2D();
  virtual uint32_t GetWidth() const override { return width; };
  virtual uint32_t GetHeight() const override { return height; };
  virtual void bind(uint32_t slot = 0) const override;
};

} // namespace v6
