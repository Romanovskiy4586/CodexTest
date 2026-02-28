#include "engine/Application.hpp"

#include "engine/Engine.hpp"

#include <GLFW/glfw3.h>

namespace {

struct InputState {
  engine::Camera* camera{nullptr};
  double lastX{0.0};
  double lastY{0.0};
  bool firstMouse{true};
};

} // namespace

namespace engine {

Application::Application(IClientLayer& clientLayer) : m_clientLayer(clientLayer) {}

void Application::run() {
  Engine engine(1280, 720, "Light3D Engine");
  auto& window = engine.window();
  auto& camera = engine.camera();

  InputState inputState{};
  inputState.camera = &camera;

  glfwSetWindowUserPointer(window.native(), &inputState);
  glfwSetCursorPosCallback(window.native(), [](GLFWwindow* nativeWindow, double xPos, double yPos) {
    auto* state = static_cast<InputState*>(glfwGetWindowUserPointer(nativeWindow));
    if (state->firstMouse) {
      state->lastX = xPos;
      state->lastY = yPos;
      state->firstMouse = false;
    }

    const float xOffset = static_cast<float>(xPos - state->lastX);
    const float yOffset = static_cast<float>(state->lastY - yPos);
    state->lastX = xPos;
    state->lastY = yPos;
    state->camera->processMouse(xOffset, yOffset);
  });

  m_clientLayer.onAttach(engine);

  float previousTime = static_cast<float>(glfwGetTime());
  while (!window.shouldClose()) {
    const float now = static_cast<float>(glfwGetTime());
    const float deltaTime = now - previousTime;
    previousTime = now;

    if (glfwGetKey(window.native(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window.native(), GLFW_TRUE);
    }

    const bool forward = glfwGetKey(window.native(), GLFW_KEY_W) == GLFW_PRESS;
    const bool backward = glfwGetKey(window.native(), GLFW_KEY_S) == GLFW_PRESS;
    const bool left = glfwGetKey(window.native(), GLFW_KEY_A) == GLFW_PRESS;
    const bool right = glfwGetKey(window.native(), GLFW_KEY_D) == GLFW_PRESS;
    camera.processKeyboard(deltaTime, forward, backward, left, right);

    int framebufferWidth = 1;
    int framebufferHeight = 1;
    glfwGetFramebufferSize(window.native(), &framebufferWidth, &framebufferHeight);
    const float aspectRatio = static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight > 0 ? framebufferHeight : 1);

    m_clientLayer.onUpdate(engine, deltaTime, now);
    engine.renderer().beginFrame();
    m_clientLayer.onRender(engine, aspectRatio, now);

    window.swapBuffers();
    window.pollEvents();
  }
}

} // namespace engine
