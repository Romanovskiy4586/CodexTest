#include "engine/Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace engine {

Renderer::Renderer() {
  glEnable(GL_DEPTH_TEST);
}

void Renderer::beginFrame() const {
  glClearColor(0.1F, 0.12F, 0.15F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderMesh(const Camera& camera,
                          const Mesh& mesh,
                          const Shader& shader,
                          float aspectRatio,
                          const glm::mat4& model,
                          const Material& material,
                          const Light& light) const {
  shader.bind();

  const glm::mat4 view = camera.viewMatrix();
  const glm::mat4 projection = glm::perspective(glm::radians(60.0F), aspectRatio, 0.1F, 100.0F);

  shader.setMat4("uModel", model);
  shader.setMat4("uView", view);
  shader.setMat4("uProjection", projection);
  shader.setVec3("uViewPos", camera.position());

  shader.setVec3("uMaterial.ambient", material.ambient);
  shader.setVec3("uMaterial.diffuse", material.diffuse);
  shader.setVec3("uMaterial.specular", material.specular);
  shader.setFloat("uMaterial.shininess", material.shininess);

  shader.setVec3("uLight.position", light.position);
  shader.setVec3("uLight.ambient", light.ambient);
  shader.setVec3("uLight.diffuse", light.diffuse);
  shader.setVec3("uLight.specular", light.specular);

  mesh.draw();
}

} // namespace engine
