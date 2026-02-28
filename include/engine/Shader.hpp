#pragma once

#include <glm/glm.hpp>

#include <string>

namespace engine {

class Shader {
public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  ~Shader();

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  void bind() const;
  [[nodiscard]] unsigned int id() const;

  void setMat4(const std::string& name, const glm::mat4& value) const;
  void setVec3(const std::string& name, const glm::vec3& value) const;
  void setFloat(const std::string& name, float value) const;

private:
  unsigned int m_programId;
};

} // namespace engine
