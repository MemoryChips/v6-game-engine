// #include "hzpch.h"
#include "opengl-shader.h"
#include "core.h"
#include "log.h"
#include "vector"

#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace v6 {

OpenGLShader::OpenGLShader(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {
  // Create an empty vertex shader handle
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  const GLchar *source = vertexSrc.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  // Compile the vertex shader
  glCompileShader(vertexShader);

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(vertexShader);

    LOG_CORE_ERROR("{0}", infoLog.data());
    V6_CORE_ASSERT(false, "Vertex shader compilation failure!");
    return;
  }

  // Create an empty fragment shader handle
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Send the fragment shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = fragmentSrc.c_str();
  glShaderSource(fragmentShader, 1, &source, 0);

  // Compile the fragment shader
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    // We don't need the shader anymore.
    glDeleteShader(fragmentShader);
    // Either of them. Don't leak shaders.
    glDeleteShader(vertexShader);

    LOG_CORE_ERROR("{0}", infoLog.data());
    V6_CORE_ASSERT(false, "Fragment shader compilation failure!");
    return;
  }

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  rendererId = glCreateProgram();
  GLuint program = rendererId;

  // Attach our shaders to our program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(program);
    // Don't leak shaders either.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    LOG_CORE_ERROR("{0}", infoLog.data());
    V6_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  // Always detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(rendererId); }

void OpenGLShader::bind() const { glUseProgram(rendererId); }

void OpenGLShader::unbind() const { glUseProgram(0); }

void OpenGLShader::UploadUniformInt(const std::string &name, const int &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform1i(location, v);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, const float &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform1f(location, v);
}

void OpenGLShader::UploadUniformFloat2(const std::string &name,
                                       const glm::vec2 &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform2f(location, v.x, v.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string &name,
                                       const glm::vec3 &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform3f(location, v.x, v.y, v.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string &name,
                                       const glm::vec4 &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform4f(location, v.x, v.y, v.z, v.w);
}

void OpenGLShader::UploadUniformMat3(const std::string &name,
                                     const glm::mat3 &matrix) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string &name,
                                     const glm::mat4 &matrix) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace v6