#include "engine/Application.hpp"
#include "engine/Engine.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <exception>
#include <iostream>
#include <memory>

namespace {

class SandboxClient final : public engine::IClientLayer {
public:
  void onAttach(engine::Engine& engine) override {
    m_shader = engine.createShader("shaders/blinn_phong.vert", "shaders/blinn_phong.frag");
    m_cube = std::make_unique<engine::Mesh>(engine::Mesh::cube());
    m_plane = std::make_unique<engine::Mesh>(engine::Mesh::plane(3.0F));
    m_pyramid = std::make_unique<engine::Mesh>(engine::Mesh::pyramid());
  }

  void onUpdate(engine::Engine&, float, float timeSeconds) override {
    m_light.position = {2.0F * std::cos(timeSeconds), 1.8F, 2.0F * std::sin(timeSeconds)};
  }

  void onRender(engine::Engine& engine, float aspectRatio, float timeSeconds) override {
    const auto& camera = engine.camera();
    auto& renderer = engine.renderer();

    engine::Material cubeMaterial{};
    cubeMaterial.diffuse = {0.3F, 0.72F, 0.98F};

    engine::Material pyramidMaterial{};
    pyramidMaterial.diffuse = {0.95F, 0.55F, 0.25F};

    engine::Material planeMaterial{};
    planeMaterial.ambient = {0.15F, 0.15F, 0.18F};
    planeMaterial.diffuse = {0.35F, 0.35F, 0.4F};
    planeMaterial.specular = {0.3F, 0.3F, 0.3F};
    planeMaterial.shininess = 16.0F;

    const glm::mat4 cubeModel = glm::translate(glm::mat4(1.0F), glm::vec3(-1.2F, 0.75F, 0.0F)) *
                                glm::rotate(glm::mat4(1.0F), timeSeconds * 0.8F, glm::vec3(0.2F, 1.0F, 0.0F));
    renderer.renderMesh(camera, *m_cube, *m_shader, aspectRatio, cubeModel, cubeMaterial, m_light);

    const glm::mat4 pyramidModel = glm::translate(glm::mat4(1.0F), glm::vec3(1.3F, 0.0F, -0.6F));
    renderer.renderMesh(camera, *m_pyramid, *m_shader, aspectRatio, pyramidModel, pyramidMaterial, m_light);

    const glm::mat4 planeModel = glm::mat4(1.0F);
    renderer.renderMesh(camera, *m_plane, *m_shader, aspectRatio, planeModel, planeMaterial, m_light);
  }

private:
  engine::Light m_light{};
  std::unique_ptr<engine::Shader> m_shader;
  std::unique_ptr<engine::Mesh> m_cube;
  std::unique_ptr<engine::Mesh> m_plane;
  std::unique_ptr<engine::Mesh> m_pyramid;
};

} // namespace

int main() {
  try {
    SandboxClient client;
    engine::Application app(client);
    app.run();
    return 0;
  } catch (const std::exception& ex) {
    std::cerr << "Fatal error: " << ex.what() << '\n';
    return 1;
  }
}
