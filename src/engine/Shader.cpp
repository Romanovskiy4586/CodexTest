#include "engine/Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::string readFile(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Failed to open shader file: " + path);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

unsigned int compileShader(unsigned int type, const std::string& source) {
  const unsigned int shader = glCreateShader(type);
  const char* sourcePtr = source.c_str();
  glShaderSource(shader, 1, &sourcePtr, nullptr);
  glCompileShader(shader);

  int success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE) {
    int logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(static_cast<size_t>(logLength));
    glGetShaderInfoLog(shader, logLength, nullptr, log.data());
    throw std::runtime_error("Shader compile error: " + std::string(log.data()));
  }

  return shader;
}

} // namespace

namespace engine {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_programId(0) {
  const std::string vertexSource = readFile(vertexPath);
  const std::string fragmentSource = readFile(fragmentPath);

  const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
  const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

  m_programId = glCreateProgram();
  glAttachShader(m_programId, vertexShader);
  glAttachShader(m_programId, fragmentShader);
  glLinkProgram(m_programId);

  int success = 0;
  glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
  if (success != GL_TRUE) {
    int logLength = 0;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> log(static_cast<size_t>(logLength));
    glGetProgramInfoLog(m_programId, logLength, nullptr, log.data());
    throw std::runtime_error("Program link error: " + std::string(log.data()));
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  if (m_programId != 0U) {
    glDeleteProgram(m_programId);
  }
}

void Shader::bind() const {
  glUseProgram(m_programId);
}

unsigned int Shader::id() const {
  return m_programId;
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
  const int location = glGetUniformLocation(m_programId, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
  const int location = glGetUniformLocation(m_programId, name.c_str());
  glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setFloat(const std::string& name, float value) const {
  const int location = glGetUniformLocation(m_programId, name.c_str());
  glUniform1f(location, value);
}

} // namespace engine
