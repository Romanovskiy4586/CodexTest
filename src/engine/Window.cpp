#include "engine/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace engine {

Window::Window(int width, int height, const char* title) : m_window(nullptr), m_width(width), m_height(height) {
  if (glfwInit() != GLFW_TRUE) {
    throw std::runtime_error("glfwInit failed");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (m_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("glfwCreateWindow failed");
  }

  glfwMakeContextCurrent(m_window);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
    throw std::runtime_error("gladLoadGLLoader failed");
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });
}

Window::~Window() {
  if (m_window != nullptr) {
    glfwDestroyWindow(m_window);
  }
  glfwTerminate();
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(m_window) != 0;
}

void Window::swapBuffers() const {
  glfwSwapBuffers(m_window);
}

void Window::pollEvents() const {
  glfwPollEvents();
}

GLFWwindow* Window::native() const {
  return m_window;
}

int Window::width() const {
  return m_width;
}

int Window::height() const {
  return m_height;
}

} // namespace engine
