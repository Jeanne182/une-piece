#include <string>
#include <iostream>

#include <class/AssetManager.hpp>
#include <class/Model.hpp>
#include <class/Error.hpp>

using namespace glimac;
namespace UP
{
// INIT THE INSTANCE TO NULL
AssetManager *AssetManager::instance = NULL;

std::string AssetManager::saveFile(const std::string &fileName) const
{
  return _appPath.dirPath() + "../save/" + fileName;
}

std::string AssetManager::modelFile(const std::string &model) const
{
  return _appPath.dirPath() + "../../src/assets/models/" + model;
}
  
std::string AssetManager::musicFile(const std::string &music) const
{
  return _appPath.dirPath() + "../../src/assets/music/" + music;
}

std::string AssetManager::textureFile(const std::string &texture) const
{
  return _appPath.dirPath() + "../../src/assets/textures/" + texture;
}

std::string AssetManager::fontFile(const std::string &font) const
{
  return _appPath.dirPath() + "../../src/assets/fonts/" + font;
}

Model *AssetManager::model(const std::string &name)
{
  if (_models.find(name) == _models.end())
  {
    // We don't have loaded the model. Let's load it
    _models.insert(std::pair<std::string, Model *>(name, new Model(name)));
  }
  //std::cout << "Nb models in store : " << _models.size() << std::endl;
  return _models.find(name)->second;
}

Model *AssetManager::model(const std::string &name) const
{
  if (_models.find(name) != _models.end())
  {
    throw Error("No model in store", AT);
  }
  return _models.find(name)->second;
}
} // namespace UP