#include <vector>

#include <class/MapManager.hpp>
#include <class/AssetManager.hpp>
#include <class/Tile.hpp>
#include <class/Program.hpp>
#include <class/Coin.hpp>
#include <class/common.hpp>

using namespace glimac;

namespace UP
{
MapManager::MapManager()
{

  int l = 20;
  int w = 3;

  for (float i = 0.5; i < l; i++)
  {
    for (float j = 0.5; j < w; j++)
    {
      std::cout << "Coord : " << i << " | " << j << std::endl;
      _temp.push_back(new Coin(glm::vec3(i, 0.f, j-1), 1, "ruby.obj"));
    }
  }
}

void MapManager::setMatrix(const glm::mat4 &cameraMV) const
{
  for (int i = 0; i < _temp.size(); i++)
  {
    _temp[i]->setMatrix(cameraMV);
  }
}

void MapManager::display() const
{
  for (int i = 0; i < _temp.size(); i++)
  {
    _temp[i]->display();
  }
}

} // namespace UP
