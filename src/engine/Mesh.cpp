#include "engine/Mesh.hpp"

#include <glad/glad.h>

#include <cstddef>
#include <utility>

namespace engine {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_vao(0), m_vbo(0), m_ebo(0), m_indexCount(static_cast<int>(indices.size())) {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
               indices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

Mesh::~Mesh() {
  if (m_ebo != 0U) {
    glDeleteBuffers(1, &m_ebo);
  }
  if (m_vbo != 0U) {
    glDeleteBuffers(1, &m_vbo);
  }
  if (m_vao != 0U) {
    glDeleteVertexArrays(1, &m_vao);
  }
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vao(std::exchange(other.m_vao, 0U)),
      m_vbo(std::exchange(other.m_vbo, 0U)),
      m_ebo(std::exchange(other.m_ebo, 0U)),
      m_indexCount(std::exchange(other.m_indexCount, 0)) {}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
  if (this != &other) {
    this->~Mesh();
    m_vao = std::exchange(other.m_vao, 0U);
    m_vbo = std::exchange(other.m_vbo, 0U);
    m_ebo = std::exchange(other.m_ebo, 0U);
    m_indexCount = std::exchange(other.m_indexCount, 0);
  }
  return *this;
}

void Mesh::draw() const {
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
}

Mesh Mesh::cube() {
  std::vector<Vertex> vertices{
      {{-0.5F, -0.5F, 0.5F}, {0.0F, 0.0F, 1.0F}}, {{0.5F, -0.5F, 0.5F}, {0.0F, 0.0F, 1.0F}},
      {{0.5F, 0.5F, 0.5F}, {0.0F, 0.0F, 1.0F}},  {{-0.5F, 0.5F, 0.5F}, {0.0F, 0.0F, 1.0F}},

      {{-0.5F, -0.5F, -0.5F}, {0.0F, 0.0F, -1.0F}}, {{0.5F, -0.5F, -0.5F}, {0.0F, 0.0F, -1.0F}},
      {{0.5F, 0.5F, -0.5F}, {0.0F, 0.0F, -1.0F}},  {{-0.5F, 0.5F, -0.5F}, {0.0F, 0.0F, -1.0F}},

      {{-0.5F, -0.5F, -0.5F}, {-1.0F, 0.0F, 0.0F}}, {{-0.5F, -0.5F, 0.5F}, {-1.0F, 0.0F, 0.0F}},
      {{-0.5F, 0.5F, 0.5F}, {-1.0F, 0.0F, 0.0F}},  {{-0.5F, 0.5F, -0.5F}, {-1.0F, 0.0F, 0.0F}},

      {{0.5F, -0.5F, -0.5F}, {1.0F, 0.0F, 0.0F}}, {{0.5F, -0.5F, 0.5F}, {1.0F, 0.0F, 0.0F}},
      {{0.5F, 0.5F, 0.5F}, {1.0F, 0.0F, 0.0F}},  {{0.5F, 0.5F, -0.5F}, {1.0F, 0.0F, 0.0F}},

      {{-0.5F, 0.5F, 0.5F}, {0.0F, 1.0F, 0.0F}}, {{0.5F, 0.5F, 0.5F}, {0.0F, 1.0F, 0.0F}},
      {{0.5F, 0.5F, -0.5F}, {0.0F, 1.0F, 0.0F}}, {{-0.5F, 0.5F, -0.5F}, {0.0F, 1.0F, 0.0F}},

      {{-0.5F, -0.5F, 0.5F}, {0.0F, -1.0F, 0.0F}}, {{0.5F, -0.5F, 0.5F}, {0.0F, -1.0F, 0.0F}},
      {{0.5F, -0.5F, -0.5F}, {0.0F, -1.0F, 0.0F}}, {{-0.5F, -0.5F, -0.5F}, {0.0F, -1.0F, 0.0F}},
  };

  std::vector<unsigned int> indices{
      0, 1, 2, 2, 3, 0,       4, 7, 6, 6, 5, 4,       8, 9, 10, 10, 11, 8,
      12, 15, 14, 14, 13, 12, 16, 17, 18, 18, 19, 16, 20, 23, 22, 22, 21, 20,
  };

  return Mesh(vertices, indices);
}

Mesh Mesh::plane(float halfExtent) {
  const std::vector<Vertex> vertices{
      {{-halfExtent, 0.0F, -halfExtent}, {0.0F, 1.0F, 0.0F}},
      {{halfExtent, 0.0F, -halfExtent}, {0.0F, 1.0F, 0.0F}},
      {{halfExtent, 0.0F, halfExtent}, {0.0F, 1.0F, 0.0F}},
      {{-halfExtent, 0.0F, halfExtent}, {0.0F, 1.0F, 0.0F}},
  };

  const std::vector<unsigned int> indices{0, 1, 2, 2, 3, 0};
  return Mesh(vertices, indices);
}

Mesh Mesh::pyramid() {
  const std::vector<Vertex> vertices{
      {{-0.5F, 0.0F, -0.5F}, {0.0F, -1.0F, 0.0F}}, {{0.5F, 0.0F, -0.5F}, {0.0F, -1.0F, 0.0F}},
      {{0.5F, 0.0F, 0.5F}, {0.0F, -1.0F, 0.0F}},   {{-0.5F, 0.0F, 0.5F}, {0.0F, -1.0F, 0.0F}},
      {{0.0F, 0.8F, 0.0F}, {0.0F, 0.707F, -0.707F}}, {{0.0F, 0.8F, 0.0F}, {0.707F, 0.707F, 0.0F}},
      {{0.0F, 0.8F, 0.0F}, {0.0F, 0.707F, 0.707F}},  {{0.0F, 0.8F, 0.0F}, {-0.707F, 0.707F, 0.0F}},
      {{-0.5F, 0.0F, -0.5F}, {0.0F, 0.707F, -0.707F}}, {{0.5F, 0.0F, -0.5F}, {0.0F, 0.707F, -0.707F}},
      {{0.5F, 0.0F, -0.5F}, {0.707F, 0.707F, 0.0F}},   {{0.5F, 0.0F, 0.5F}, {0.707F, 0.707F, 0.0F}},
      {{0.5F, 0.0F, 0.5F}, {0.0F, 0.707F, 0.707F}},   {{-0.5F, 0.0F, 0.5F}, {0.0F, 0.707F, 0.707F}},
      {{-0.5F, 0.0F, 0.5F}, {-0.707F, 0.707F, 0.0F}}, {{-0.5F, 0.0F, -0.5F}, {-0.707F, 0.707F, 0.0F}},
  };

  const std::vector<unsigned int> indices{
      0, 1, 2, 2, 3, 0,
      8, 9, 4,
      10, 11, 5,
      12, 13, 6,
      14, 15, 7,
  };

  return Mesh(vertices, indices);
}

} // namespace engine
