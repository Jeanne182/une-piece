#ifndef MESH_UP_HPP__
#define MESH_UP_HPP__

#pragma once

#include <vector>
#include <map>
#include <class/common.hpp>

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
   */
  Mesh(std::vector<ShapeVertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  /**
   * @brief Destroy the Mesh object
   * 
   */
  ~Mesh();

  /**
   * @brief Draw a particular Mesh with it's texture at the given location
   * 
   */
  void draw() const;

  // DATA
  GLuint _VAO, _VBO, _EBO;
private:
  //  Mesh Data
  std::vector<ShapeVertex> _vertices;
  std::vector<unsigned int> _indices;
  std::vector<Texture> _textures;
  // Constructor
  void setupMesh();
};

} // namespace UP

#endif