#pragma once

#include "engine/Camera.hpp"
#include "engine/Mesh.hpp"
#include "engine/Shader.hpp"

#include <glm/glm.hpp>

namespace engine {

struct Material {
  glm::vec3 ambient{0.2F, 0.2F, 0.25F};
  glm::vec3 diffuse{0.5F, 0.7F, 0.9F};
  glm::vec3 specular{0.95F, 0.95F, 0.95F};
  float shininess{64.0F};
};

struct Light {
  glm::vec3 position{2.0F, 2.0F, 2.0F};
  glm::vec3 ambient{0.06F, 0.06F, 0.08F};
  glm::vec3 diffuse{0.9F, 0.9F, 0.9F};
  glm::vec3 specular{1.0F, 1.0F, 1.0F};
};

class Renderer {
public:
  Renderer();

  void beginFrame() const;
  void renderMesh(const Camera& camera,
                  const Mesh& mesh,
                  const Shader& shader,
                  float aspectRatio,
                  const glm::mat4& model,
                  const Material& material,
                  const Light& light) const;
};

} // namespace engine
