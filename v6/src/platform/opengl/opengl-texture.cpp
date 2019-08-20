#include "opengl-texture.h"
#include "core.h"
#include "glad/glad.h"
#include "log.h"
#include "stb-image.h"

namespace v6 {

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : path(path) {
  int w, h, channels;
  stbi_set_flip_vertically_on_load(1); // to accomodate open gl

  stbi_uc *data = stbi_load(path.c_str(), &w, &h, &channels, 0);
  V6_CORE_ASSERT(data, "Failed to load image");
  width = w;
  height = h;

  glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
  glTextureStorage2D(rendererId, 1, GL_RGB8, width, height);
  glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureSubImage2D(rendererId, 0, 0, 0, width, height, GL_RGB,
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
OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &rendererId); }
void OpenGLTexture2D::bind(uint32_t slot) const {
  glBindTextureUnit(slot, rendererId);
}

} // namespace v6
