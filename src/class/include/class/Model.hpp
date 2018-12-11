#ifndef MODEL_UP_HPP__
#define MODEL_UP_HPP__

#pragma once

#include <map>
#include <vector>
#include <glimac/common.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <class/Mesh.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Handle a Model from a OBJ file
 * 
 */
class Model
{
public:
  // Constructor
  /**
   * @brief Construct a new Model object
   * @brief Take in parameters the path of the model to load and the glLocation of the textures to use from the shader
   * @param path 
   * @param textureLocation 
   */
  Model(const std::string &path, const std::map<std::string, GLint> &textureLocation);

  // Methods
  /**
   * @brief Call the draw methods of each Meshes
   */
  void draw() const;

  /**
   * @brief Load a model, do the Initializing stuff
   * 
   * @param path 
   */
  void loadModel(const std::string &path);

  /**
   * @brief Reccursive function to load all the Nodes of an imported aiScene of the Model
   * 
   * @param node 
   * @param scene 
   */
  void processNode(const aiNode *node, const aiScene *scene);

  /**
   * @brief Reccursive function to load all the Meshes of a Node
   * 
   * @param mesh 
   * @param scene 
   * @return Mesh 
   */
  Mesh processMesh(const aiMesh *mesh, const aiScene *scene);

  /**
   * @brief Helper function to load all the textures from a material of a Node
   * 
   * @param mat 
   * @param type 
   * @param typeName 
   * @return std::vector<Texture> 
   */
  std::vector<Texture> loadMaterialTextures(const aiMaterial *mat, const aiTextureType &type, const std::string &typeName);

private:
  std::vector<Mesh> _meshes;
  std::string _directory;
  std::vector<Texture> _textures_loaded;
  std::map<std::string, GLint> _texturesLocation;
};

} // namespace UP

#endif
