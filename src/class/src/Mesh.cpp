#include <class/AssetManager.hpp>
#include <class/Mesh.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>
#include <class/common.hpp>

#include <string>
#include <vector>
#include <exception>
#include <iostream>

using namespace glimac;

namespace UP
{

Mesh::Mesh(std::vector<ShapeVertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures)
    : _vertices(vertices),
      _indices(indices),
      _textures(textures)
{
  setupMesh();
}

Mesh::~Mesh(){};

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
  for (size_t i = 0; i < _textures.size(); i++)
  {
    // retrieve texture number (the N in diffuse_textureN)
    std::string number;
    std::string name = _textures[i].type;
    const AssetProgramMultiLight &a = AssetManager::Get()->assetProgramMultiLight();
    // activate proper texture unit before binding
    glActiveTexture(GL_TEXTURE0 + i);
    if (name == "uTexture_diffuse")
    {
      number = std::to_string(diffuseNr++);

      // Send the info of the first texture found
      glUniform1f(a.uShininess, _textures[i].shininess);
      glUniform3fv(a.uKd, 1, glm::value_ptr(_textures[i].diffuse));
      glUniform3fv(a.uKs, 1, glm::value_ptr(_textures[i].specular));
    }
    else if (name == "uTexture_specular")
    {
      number = std::to_string(specularNr++);
    }

    GLint location = a.uMapTextures.at(std::string(name + number));
    glUniform1i(location, i);
    glBindTexture(GL_TEXTURE_2D, _textures[i].id);
  }

  // draw mesh
  glBindVertexArray(_VAO);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  // Unbind
  for (size_t i = 0; i < _textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

} // namespace UP