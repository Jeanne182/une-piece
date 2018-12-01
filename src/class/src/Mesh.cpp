#include <class/Mesh.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>
/*
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
*/
#include <string>
#include <vector>
#include <exception>
#include <iostream>

using namespace glimac;

namespace UP
{

Mesh::Mesh(std::vector<ShapeVertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures,
           std::map<std::string, GLint> texturesLocation)
    : _vertices(vertices),
      _indices(indices),
      _textures(textures),
      _texturesLocation(texturesLocation)
{
  setupMesh();
  std::cout << "Indices: " << _indices.size() << std::endl;
  std::cout << "Vertices: " << _vertices.size() << std::endl;
  std::cout << "Textures: " << _textures.size() << std::endl;

  /*
  for(size_t i=0; i<_vertices.size(); i++) {
    std::cout << _vertices[i].position << " | " << _vertices[i].normal << std::endl;
  }
  */
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

  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_NORMAL = 1;
  const GLuint VERTEX_ATTR_COORDS = 2;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glEnableVertexAttribArray(VERTEX_ATTR_COORDS);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, position));
  glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, normal));
  glVertexAttribPointer(VERTEX_ATTR_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (void *)offsetof(ShapeVertex, texCoords));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glCheckError();
}

void Mesh::draw() const
{
  // Use Textures
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  unsigned int normalNr = 1;
  unsigned int heightNr = 1;
  for (size_t i = 0; i < _textures.size(); i++)
  {
    // activate proper texture unit before binding
    glActiveTexture(GL_TEXTURE0 + i);
    // retrieve texture number (the N in diffuse_textureN)
    std::string number;
    std::string name = _textures[i].type;
    if (name == "uTexture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "uTexture_specular")
      number = std::to_string(specularNr++);
    /*
    else if (name == "uTexture_normal")
      number = std::to_string(normalNr++);
    else if (name == "uTexture_height")
      number = std::to_string(heightNr++);
    */

    GLint location = _texturesLocation.at(name + number);
    glUniform1i(location, i);
    glBindTexture(GL_TEXTURE_2D, _textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  // draw mesh
  glBindVertexArray(_VAO);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace UP