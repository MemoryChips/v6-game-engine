#include "platform/opengl/opengl-buffer.h"
#include "instrumentor.h"
#include <glad/glad.h>

namespace v6 {

/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
  V6_PROFILE_FUNCTION();
  glCreateBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  V6_PROFILE_FUNCTION();
  glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind() const {
  V6_PROFILE_FUNCTION();
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const {
  V6_PROFILE_FUNCTION();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
    : m_Count(count) {
  V6_PROFILE_FUNCTION();
  glCreateBuffers(1, &m_RendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
  V6_PROFILE_FUNCTION();
  glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::Bind() const {
  V6_PROFILE_FUNCTION();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const {
  V6_PROFILE_FUNCTION();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace v6
