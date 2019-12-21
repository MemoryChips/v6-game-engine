// #include "hzpch.h"
#include "opengl-shader.h"
#include "core.h"
#include "instrumentor.h"
#include "log.h"
#include <array>
#include <vector>

#include <fstream>
// #include <iostream>
// #include <sstream>

#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace v6 {

static GLenum shaderTypeFromString(const std::string &type) {
  if (type == "vertex")
    return GL_VERTEX_SHADER;
  if (type == "fragment" || type == "pixel")
    return GL_FRAGMENT_SHADER;
  V6_CORE_ASSERT(false, "Unknown shader type")
  return 0;
}

OpenGLShader::OpenGLShader(const std::string &filePath) {
  V6_PROFILE_FUNCTION();
  std::string source = readFile(filePath);
  auto shaderSources = preProcess(source);
  compile(shaderSources);
  // Extract name from filepath
  auto lastSlash = filePath.find_last_of("/\\");
  lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
  auto lastDot = filePath.rfind('.');
  auto count = lastDot == std::string::npos ? filePath.size() - lastSlash
                                            : lastDot - lastSlash;
  name = filePath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string &name,
                           const std::string &vertexSrc,
                           const std::string &fragmentSrc)
    : name(name) {
  V6_PROFILE_FUNCTION();
  std::unordered_map<GLenum, std::string> shaderSources;
  shaderSources[GL_VERTEX_SHADER] = vertexSrc;
  shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
  compile(shaderSources);
}

void OpenGLShader::compile(
    const std::unordered_map<GLenum, std::string> &shaderSources) {

  V6_PROFILE_FUNCTION();
  GLuint program = glCreateProgram();
#define NUM_SHADERS 12
  V6_CORE_ASSERT(shaderSources.size() <= NUM_SHADERS,
                 "We only support limited shaders for now");
  std::array<GLenum, NUM_SHADERS> glShaderIds;
  unsigned int glShaderIDIndex = 0;

  for (auto &kv : shaderSources) {
    const GLenum type = kv.first;
    const std::string &source = kv.second;

    GLuint shader = glCreateShader(type);

    const GLchar *sourceCstr = source.c_str();
    glShaderSource(shader, 1, &sourceCstr, 0);

    // Compile the vertex shader
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      glDeleteShader(shader);

      LOG_CORE_ERROR("{0}", infoLog.data());
      V6_CORE_ASSERT(false, "Shader compilation failure!");
      break;
    }
    glAttachShader(program, shader);
    glShaderIds[glShaderIDIndex++] = shader;
  }

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
    for (auto shaderId : glShaderIds) {
      glDeleteShader(shaderId);
    }

    LOG_CORE_ERROR("{0}", infoLog.data());
    V6_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  // Always detach shaders after a successful link.
  for (unsigned int shaderId = 0; shaderId < glShaderIDIndex; shaderId++) {
    glDetachShader(program, glShaderIds[shaderId]);
    glDeleteShader(glShaderIds[shaderId]);
  }
  // Hazel code has a bug. It should be as follows but likely cleaned up in the
  // future This code runs thru entire 12 position array so it fails also for
  // (auto id : glShaderIds) {
  //   glDetachShader(program, glShaderIds[id]);
  //   glDeleteShader(glShaderIds[id]);
  // }

  rendererId = program;
}

OpenGLShader::~OpenGLShader() {
  V6_PROFILE_FUNCTION();
  glDeleteProgram(rendererId);
}

std::unordered_map<GLenum, std::string>
OpenGLShader::preProcess(const std::string &source) {
  V6_PROFILE_FUNCTION();
  std::unordered_map<GLenum, std::string> shaderSources;
  const char *typeToken = "#type";
  size_t typeTokenLength = strlen(typeToken);
  size_t pos = source.find(typeToken, 0);
  while (pos != std::string::npos) {
    size_t eol = source.find_first_of("\r\n", pos);
    V6_CORE_ASSERT(eol != std::string::npos, "Syntax error");
    size_t begin = pos + typeTokenLength + 1;
    std::string type = source.substr(begin, eol - begin);
    // V6_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel",
    V6_CORE_ASSERT(shaderTypeFromString(type), "Invalid shadeer type specified")

    size_t nextLinePos = source.find_first_not_of("\r\n", eol);
    pos = source.find(typeToken, nextLinePos);
    size_t finalLinePos =
        pos -
        (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos);
    shaderSources[shaderTypeFromString(type)] =
        source.substr(nextLinePos, finalLinePos);
  }
  return shaderSources;
}

std::string OpenGLShader::readFile(const std::string &filePath) {
  V6_PROFILE_FUNCTION();
  std::ifstream in(filePath, std::ios::in | std::ios::binary);
  std::string result;
  if (in) {
    in.seekg(0, std::ios::end);
    auto size = in.tellg();
    if (size != -1) {
      result.resize(size);
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
      in.close();
    } else {
      LOG_ERROR("Could not read from file '{0}'", filePath);
    }
  } else {
    LOG_ERROR("Could not open file: '{0}'", filePath);
  }
  return result;
}

void OpenGLShader::bind() const {
  V6_PROFILE_FUNCTION();
  glUseProgram(rendererId);
}

void OpenGLShader::unbind() const {
  V6_PROFILE_FUNCTION();
  glUseProgram(0);
}

void OpenGLShader::setInt(const std::string &name, int value) {
  V6_PROFILE_FUNCTION();
  UploadUniformInt(name, value);
}

void OpenGLShader::setFloat(const std::string &name, const float &f) {
  V6_PROFILE_FUNCTION();
  UploadUniformFloat(name, f);
}

void OpenGLShader::setFloat3(const std::string &name, const glm::vec3 &f) {
  V6_PROFILE_FUNCTION();
  UploadUniformFloat3(name, f);
}
void OpenGLShader::setFloat4(const std::string &name, const glm::vec4 &f) {
  V6_PROFILE_FUNCTION();
  UploadUniformFloat4(name, f);
}
void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &m) {
  V6_PROFILE_FUNCTION();
  UploadUniformMat4(name, m);
}

void OpenGLShader::UploadUniformInt(const std::string &name, const int &v) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform1i(location, v);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, const float &f) {
  GLint location = glGetUniformLocation(rendererId, name.c_str());
  glUniform1f(location, f);
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
