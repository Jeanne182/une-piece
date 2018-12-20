#ifndef MODEL_UP_HPP__
#define MODEL_UP_HPP__

#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <class/common.hpp>
#include <class/Mesh.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Handle a Model from an OBJ file
 * 
 */
class Model
{
public:
  // Constructor
  /**
   * @brief Construct a new Model object
   * 
   * @param name 
   * @param textureRepeat 
   */
  Model(const std::string &name, const float &textureRepeat = 1.0f);

  /**
   * @brief Destroy the Model object
   * 
   */
  ~Model();

  // Methods
  /**
   * @brief Call the draw methods of each Meshes
   */
  void draw() const;

  /**
   * @brief Load a model, do the Initializing stuff
   * 
   * @param name 
   */
  void loadModel(const std::string &name);

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
   * @brief Get the Repeat object
   * 
   * @return float 
   */
  inline float getRepeat() const { return _textureRepeat; };
  /**
   * @brief Set the Repeat object
   * 
   * @param r 
   */
  inline void setRepeat(const float &r) { _textureRepeat = r; };

  void check() const
  {
    std::cout << "Amount of meshes : " << _meshes.size() << std::endl;
  }

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
  const std::string _name;
  float _textureRepeat;
  std::vector<Texture> _textures_loaded;
};

} // namespace UP

#endif
