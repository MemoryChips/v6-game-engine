#include "opengl-texture.h"
#include "core.h"
#include "glad/glad.h"
#include "instrumentor.h"
#include "log.h"
#include "stb-image.h"

namespace v6 {

OpenGLTexture2D::OpenGLTexture2D(uint32_t w, uint32_t h) : width(w), height(h) {
  V6_PROFILE_FUNCTION();
  internalFormat = GL_RGBA8;
  dataFormat = GL_RGBA;

  glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
  glTextureStorage2D(rendererId, 1, internalFormat, width, height);

  glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : path(path) {
  V6_PROFILE_FUNCTION();
  int w, h, channels;
  stbi_set_flip_vertically_on_load(1); // to accomodate open gl
  stbi_uc *data = nullptr;
  {
    V6_PROFILE_SCOPE(
        "stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string)");
    data = stbi_load(path.c_str(), &w, &h, &channels, 0);
  }
  V6_CORE_ASSERT(data, "Failed to load image");
  width = w;
  height = h;

  // GLenum internalFormat = 0, dataFormat = 0;
  if (channels == 4) {
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;
  } else if (channels == 3) {
    internalFormat = GL_RGB8;
    dataFormat = GL_RGB;
  }

  V6_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
  glTextureStorage2D(rendererId, 1, internalFormat, width, height);

  glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTextureSubImage2D(rendererId, 0, 0, 0, width, height, dataFormat,
                      GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
  // glGenTextures(1, &rendererId);
  // glBindTexture(GL_TEXTURE_2D, rendererId);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
  //                     GL_UNSIGNED_BYTE, data);
}
OpenGLTexture2D::~OpenGLTexture2D() {
  V6_PROFILE_FUNCTION();
  glDeleteTextures(1, &rendererId);
}

void OpenGLTexture2D::setData(void *pData, uint32_t size) const {
  V6_PROFILE_FUNCTION();
  uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
  V6_CORE_ASSERT(size == width * height * bpp, "Data must be entire texture!");
  glTextureSubImage2D(rendererId, 0, 0, 0, width, height, dataFormat,
                      GL_UNSIGNED_BYTE, pData);
}

void OpenGLTexture2D::bind(uint32_t slot) const {
  V6_PROFILE_FUNCTION();
  glBindTextureUnit(slot, rendererId);
}

} // namespace v6
