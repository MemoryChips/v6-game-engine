#include "opengl-texture.h"
#include "glad/glad.h"

namespace v6 {

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : path(path) {}
OpenGLTexture2D::~OpenGLTexture2D() {}
void OpenGLTexture2D::bind() const {}

} // namespace v6
