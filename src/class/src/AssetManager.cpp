#include <string>
#include <iostream>

#include <class/AssetManager.hpp>
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

std::string AssetManager::model(const std::string &model) const
{
  return _appPath.dirPath() + "../../src/assets/models/" + model;
}

std::string AssetManager::texture(const std::string &texture) const
{
  return _appPath.dirPath() + "../../src/assets/textures/" + texture;
}
} // namespace UP