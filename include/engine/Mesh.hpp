#pragma once

#include "engine/Vertex.hpp"

#include <vector>

namespace engine {

class Mesh {
public:
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
  ~Mesh();

  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  Mesh(Mesh&& other) noexcept;
  Mesh& operator=(Mesh&& other) noexcept;

  void draw() const;

  static Mesh cube();
  static Mesh plane(float halfExtent = 1.0F);
  static Mesh pyramid();

private:
  unsigned int m_vao;
  unsigned int m_vbo;
  unsigned int m_ebo;
  int m_indexCount;
};

} // namespace engine
