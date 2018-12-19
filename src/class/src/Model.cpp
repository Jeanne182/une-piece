#include <class/Model.hpp>
#include <class/Error.hpp>
#include <class/AssetManager.hpp>

#include <glimac/Image.hpp>
#include <class/common.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <SOIL.h>

using namespace glimac;

namespace UP
{

GLint CreateTexture(const std::string &filepath);

Model::Model(const std::string &name, const float &textureRepeat)
    : _name(name),
      _textureRepeat(textureRepeat)
{
  loadModel(name);
}

Model::~Model()
{
  //std::cout << "Destroying Model : " << _directory << std::endl;
  for (size_t i = 0; i < _textures_loaded.size(); i++)
  {
    glDeleteTextures(1, &(_textures_loaded[i].id));
  }
  for (size_t i = 0; i < _meshes.size(); i++)
  {
    //std::cout << "Destroying Mesh : " << i << std::endl;
    glDeleteBuffers(1, &(_meshes[i]._VBO));
    glDeleteBuffers(1, &(_meshes[i]._EBO));
    glDeleteVertexArrays(1, &(_meshes[i]._VAO));
  }
}

void Model::loadModel(const std::string &name)
{
  Assimp::Importer importer;
  //const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
  const aiScene *scene = importer.ReadFile(AssetManager::Get()->modelFile(name),
                                           aiProcess_CalcTangentSpace |
                                               aiProcess_Triangulate |
                                               aiProcess_JoinIdenticalVertices |
                                               aiProcess_SortByPType);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    throw Error(std::string("Error Assimp: ") + importer.GetErrorString(), AT);

  _directory = AssetManager::Get()->modelFile(name).substr(0, AssetManager::Get()->modelFile(name).find_last_of('/'));
  processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode *node, const aiScene *scene)
{
  // Process all of the Node's Meshes
  for (size_t i = 0; i < node->mNumMeshes; i++)
  {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    _meshes.push_back(processMesh(mesh, scene));
  }

  // Then procceed all of it's children
  for (size_t i = 0; i < node->mNumChildren; i++)
    processNode(node->mChildren[i], scene);
};

Mesh Model::processMesh(const aiMesh *mesh, const aiScene *scene)
{
  std::vector<ShapeVertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<UP::Texture> textures;

  // Process Vertex
  for (size_t i = 0; i < mesh->mNumVertices; i++)
  {
    ShapeVertex v;

    // Position
    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    v.position = vector;

    // Normals
    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    v.normal = vector;

    // Texture
    if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
    {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      v.texCoords = vec;
    }
    else
      v.texCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(v);
  }

  // Process indexes
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  // Process Textures

  if (mesh->mMaterialIndex >= 0)
  {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "uTexture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "uTexture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  return Mesh(vertices, indices, textures);
};

GLint CreateTexture(const std::string &filepath)
{
  // Load the image

  std::unique_ptr<Image> img = loadImage(filepath);
  if (img == NULL)
  {
    throw Error(std::string("Texture failed to load at path: ") + filepath, AT);
  }

  // Setup it
  GLuint textureID;
  glGenTextures(1, &textureID);

  // Assign texture to ID
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               img->getWidth(),
               img->getHeight(),
               0,
               GL_RGBA,
               GL_FLOAT,
               img->getPixels());
  glGenerateMipmap(GL_TEXTURE_2D);

  // Parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbind
  glBindTexture(GL_TEXTURE_2D, 0);
  return textureID;
}

std::vector<Texture> Model::loadMaterialTextures(const aiMaterial *mat, const aiTextureType &type, const std::string &typeName)
{
  std::vector<Texture> textures;
  for (size_t i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;

    mat->GetTexture(type, i, &str);

    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    bool skip = false;
    for (size_t j = 0; j < _textures_loaded.size(); j++)
    {
      if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0)
      {
        textures.push_back(_textures_loaded[j]);
        skip = true;
        break;
      }
    }
    if (!skip)
    { // if texture hasn't been loaded already, load it
      UP::Texture texture;
      // Basic Data
      texture.id = CreateTexture(AssetManager::Get()->modelFile(str.C_Str()));
      texture.type = typeName;
      texture.path = str.C_Str();

      // Light Data
      aiColor3D diffuse(0.f, 0.f, 0.f);
      aiColor3D specular(0.f, 0.f, 0.f);
      float shininess;

      mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
      mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
      mat->Get(AI_MATKEY_SHININESS, shininess);

      texture.diffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
      texture.specular = glm::vec3(specular.r, specular.g, specular.b);
      texture.shininess = shininess;

      textures.push_back(texture);
      _textures_loaded.push_back(texture); // add to loaded textures
    }
  }
  return textures;
}

void Model::draw() const
{
  glUniform1f(AssetManager::Get()->assetProgramMultiLight().uTextureRepeat, _textureRepeat);
  for (size_t i = 0; i < _meshes.size(); i++)
    _meshes[i].draw();
}
} // namespace UP