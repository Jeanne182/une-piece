#include <class/Model.hpp>
#include <class/Error.hpp>
//#include <glimac/Program.hpp>
#include <glimac/common.hpp>
//#include <glimac/Image.hpp>
//#include <glimac/FilePath.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <SOIL.h>

using namespace glimac;

namespace UP
{

Model::Model(const std::string &path, const std::map<std::string, GLint> &textureLocation)
    : _texturesLocation(textureLocation)
{
  loadModel(path);
}
void Model::loadModel(const std::string &path)
{
  Assimp::Importer importer;
  //const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
  const aiScene *scene = importer.ReadFile(path,
                                           aiProcess_CalcTangentSpace |
                                               aiProcess_Triangulate |
                                               aiProcess_JoinIdenticalVertices |
                                               aiProcess_SortByPType);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    throw Error(std::string("Error Assimp: ") + importer.GetErrorString(), AT);

  _directory = path.substr(0, path.find_last_of('/'));
  processNode(scene->mRootNode, scene);

  //std::cout << "Amount of meshes : " << _meshes.size() << std::endl;
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
  std::vector<Texture> textures;

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

  return Mesh(vertices, indices, textures, _texturesLocation);
};

GLint TextureFromFile(const char *path, std::string directory)
{
  //Generate texture ID and load texture data
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  GLuint textureID;
  glGenTextures(1, &textureID);

  int width, height;
  unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  if (!image)
  {
    throw Error(std::string("Texture failed to load at path: ") + filename, AT);
  }

  // Assign texture to ID
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbind and quit
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);
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
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), _directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      _textures_loaded.push_back(texture); // add to loaded textures
    }
  }
  return textures;
}

void Model::draw() const
{
  for (size_t i = 0; i < _meshes.size(); i++)
    _meshes[i].draw();
}
} // namespace UP