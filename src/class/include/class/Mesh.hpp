#ifndef MESH_UP_HPP__
#define MESH_UP_HPP__

#pragma once

#include <vector>
#include <map>
#include <glimac/common.hpp>

using namespace glimac;

namespace UP
{

class Mesh
{
public:
  /*  Functions  */
  Mesh(std::vector<ShapeVertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures,
       std::map<std::string, GLint> texturesLocation);
  void draw() const;

private:
  //  Mesh Data
  std::vector<ShapeVertex> _vertices;
  std::vector<unsigned int> _indices;
  std::vector<Texture> _textures;

  // OBJ Data
  GLuint _VAO, _VBO, _EBO;
  std::map<std::string, GLint> _texturesLocation;

  // Constructor
  void setupMesh();
};

} // namespace UP

#endif