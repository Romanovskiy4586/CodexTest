#include "engine/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

namespace engine {

Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : m_position(position),
      m_front(0.0F, 0.0F, -1.0F),
      m_up(0.0F, 1.0F, 0.0F),
      m_right(1.0F, 0.0F, 0.0F),
      m_worldUp(0.0F, 1.0F, 0.0F),
      m_yaw(yaw),
      m_pitch(pitch),
      m_speed(4.0F),
      m_sensitivity(0.12F) {
  updateVectors();
}

void Camera::processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right) {
  const float velocity = m_speed * deltaTime;
  if (forward) {
    m_position += m_front * velocity;
  }
  if (backward) {
    m_position -= m_front * velocity;
  }
  if (left) {
    m_position -= m_right * velocity;
  }
  if (right) {
    m_position += m_right * velocity;
  }
}

void Camera::processMouse(float xOffset, float yOffset) {
  m_yaw += xOffset * m_sensitivity;
  m_pitch += yOffset * m_sensitivity;

  if (m_pitch > 89.0F) {
    m_pitch = 89.0F;
  }
  if (m_pitch < -89.0F) {
    m_pitch = -89.0F;
  }

  updateVectors();
}

glm::mat4 Camera::viewMatrix() const {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::vec3 Camera::position() const {
  return m_position;
}

void Camera::updateVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front = glm::normalize(front);
  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));
}

} // namespace engine
