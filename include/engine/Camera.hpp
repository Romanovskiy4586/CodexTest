#pragma once

#include <glm/glm.hpp>

namespace engine {

class Camera {
public:
  Camera(glm::vec3 position, float yaw = -90.0F, float pitch = 0.0F);

  void processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right);
  void processMouse(float xOffset, float yOffset);
  [[nodiscard]] glm::mat4 viewMatrix() const;
  [[nodiscard]] glm::vec3 position() const;

private:
  void updateVectors();

  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_worldUp;
  float m_yaw;
  float m_pitch;
  float m_speed;
  float m_sensitivity;
};

} // namespace engine
