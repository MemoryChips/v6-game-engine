#pragma once

#include "renderer/texture.h"
#include <glad/glad.h>

namespace v6 {
class OpenGLTexture2D : public Texture2D {
private:
  std::string path;
  uint32_t width, height;
  uint32_t rendererId;
  GLenum internalFormat, dataFormat;

public:
  OpenGLTexture2D(uint32_t w, uint32_t h);
  OpenGLTexture2D(const std::string &path);
  ~OpenGLTexture2D();
  virtual uint32_t GetWidth() const override { return width; };
  virtual uint32_t GetHeight() const override { return height; };
  virtual void setData(void *pData, uint32_t size) const override;
  virtual void bind(uint32_t slot = 0) const override;
};

} // namespace v6
