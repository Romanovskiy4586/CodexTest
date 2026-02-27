#pragma once

struct GLFWwindow;

namespace engine {

class Window {
public:
  Window(int width, int height, const char* title);
  ~Window();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  [[nodiscard]] bool shouldClose() const;
  void swapBuffers() const;
  void pollEvents() const;
  [[nodiscard]] GLFWwindow* native() const;
  [[nodiscard]] int width() const;
  [[nodiscard]] int height() const;

private:
  GLFWwindow* m_window;
  int m_width;
  int m_height;
};

} // namespace engine
