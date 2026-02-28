#pragma once

#include "engine/Camera.hpp"
#include "engine/Mesh.hpp"
#include "engine/Renderer.hpp"
#include "engine/Shader.hpp"
#include "engine/Window.hpp"

#include <memory>
#include <string>

namespace engine {

class Engine {
public:
  Engine(int width, int height, const char* title);

  [[nodiscard]] Window& window();
  [[nodiscard]] Camera& camera();
  [[nodiscard]] Renderer& renderer();

  [[nodiscard]] std::unique_ptr<Shader> createShader(const std::string& vertexPath, const std::string& fragmentPath) const;

private:
  Window m_window;
  Camera m_camera;
  Renderer m_renderer;
};

} // namespace engine
