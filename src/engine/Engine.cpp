#include "engine/Engine.hpp"

namespace engine {

Engine::Engine(int width, int height, const char* title)
    : m_window(width, height, title), m_camera({0.0F, 1.0F, 5.0F}), m_renderer() {}

Window& Engine::window() {
  return m_window;
}

Camera& Engine::camera() {
  return m_camera;
}

Renderer& Engine::renderer() {
  return m_renderer;
}

std::unique_ptr<Shader> Engine::createShader(const std::string& vertexPath, const std::string& fragmentPath) const {
  return std::make_unique<Shader>(vertexPath, fragmentPath);
}

} // namespace engine
