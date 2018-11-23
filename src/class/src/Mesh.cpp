#include "class/Mesh.hpp"
#include "class/Error.hpp"
/*
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
*/
#include <string>
#include <vector>
#include <iostream>

using namespace glimac;

namespace UP
{

Mesh::Mesh(std::vector<ShapeVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : _vertices(vertices), _indices(indices), _textures(textures)
{
  setupMesh();
}

void Mesh::setupMesh()
{
  glGenVertexArrays(1, &_VAO);
  glGenBuffers(1, &_VBO);
  glGenBuffers(1, &_EBO);

  glBindVertexArray(_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(ShapeVertex), _vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

  // Vertex positions
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_NORMAL = 1;
  const GLuint VERTEX_ATTR_COORDS = 2;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glEnableVertexAttribArray(VERTEX_ATTR_COORDS);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, position));
  glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, normal));
  glVertexAttribPointer(VERTEX_ATTR_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, texCoords));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::draw() const
{
  // draw mesh
  glBindVertexArray(_VAO);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace UP