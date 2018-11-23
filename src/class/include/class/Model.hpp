#include <vector>
#include <glimac/common.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <class/Mesh.hpp>

using namespace glimac;

namespace UP
{

class Model
{
  public:
    // Constructor
    Model(const std::string& path);
    
    // Methods
    void draw() const;
    void loadModel(const std::string& path);
    void processNode(const aiNode* node, const aiScene* scene);
    Mesh processMesh(const aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(const aiMaterial* mat, const aiTextureType& type, const std::string& typeName);

  private:
    std::vector<Mesh> _meshes;
    std::string _directory;
    std::vector<Texture> _textures_loaded; 
};

} // namespace UP