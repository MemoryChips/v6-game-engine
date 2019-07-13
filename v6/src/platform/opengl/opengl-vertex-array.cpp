#include "opengl-vertex-array.h"
#include "log.h"

#include <glad/glad.h>

namespace v6 {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
  case v6::ShaderDataType::Float:
    return GL_FLOAT;
  case v6::ShaderDataType::Float2:
    return GL_FLOAT;
  case v6::ShaderDataType::Float3:
    return GL_FLOAT;
  case v6::ShaderDataType::Float4:
    return GL_FLOAT;
  case v6::ShaderDataType::Mat3:
    return GL_FLOAT;
  case v6::ShaderDataType::Mat4:
    return GL_FLOAT;
  case v6::ShaderDataType::Int:
    return GL_INT;
  case v6::ShaderDataType::Int2:
    return GL_INT;
  case v6::ShaderDataType::Int3:
    return GL_INT;
  case v6::ShaderDataType::Int4:
    return GL_INT;
  case v6::ShaderDataType::Bool:
    return GL_BOOL;
  case ShaderDataType::None:
    LOG_ERROR("Shader type of None being used for opengl data type");
    return GL_INVALID_ENUM;
  }

  V6_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
  glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(
    const std::shared_ptr<VertexBuffer> &vertexBuffer) {
  V6_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                 "Vertex Buffer has no layout!");

  glBindVertexArray(m_RendererID);
  vertexBuffer->Bind();

  uint32_t index = 0;
  const auto &layout = vertexBuffer->GetLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void *)element.offset);
    index++;
  }

  m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer> &indexBuffer) {
  glBindVertexArray(m_RendererID);
  indexBuffer->Bind();

  m_IndexBuffer = indexBuffer;
}

} // namespace v6