#ifndef MESH_UP_HPP__
#define MESH_UP_HPP__

#pragma once

#include <vector>
#include <map>
#include <glimac/common.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Handlme a Mesh from an OBJ file
 * 
 */
class Mesh
{
public:
  // Constructor
  /**
   * @brief Construct a new Mesh object
   * 
   * @param vertices 
   * @param indices 
   * @param textures 
   * @param texturesLocation 
   */
  Mesh(std::vector<ShapeVertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures,
       std::map<std::string, GLint> texturesLocation);

  /**
   * @brief Draw a particular Mesh with it's texture at the given location
   * 
   */
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