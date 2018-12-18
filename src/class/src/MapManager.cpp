#include <vector>

#include <class/MapManager.hpp>
#include <class/AssetManager.hpp>
#include <class/Tile.hpp>
#include <class/Program.hpp>
#include <class/Coin.hpp>
#include <class/Utils.hpp>
#include <class/common.hpp>

using namespace glimac;

namespace UP
{
MapManager::MapManager()
    : _direction(DIR_NORTH)
{
  Utils::setSeed();
  generateBatch();
}

void MapManager::setMatrix(const glm::mat4 &cameraMV) const
{
  std::deque<Tile>::const_iterator it;
  for (it = _map.cbegin(); it != _map.cend(); ++it)
  {
    (*it).setMatrix(cameraMV);
  }
}

void MapManager::display() const
{
  std::deque<Tile>::const_iterator it;
  for (it = _map.cbegin(); it != _map.cend(); ++it)
  {
    (*it).display();
  }
}

void MapManager::generateBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  std::cout << "__ New Batch __" << std::endl;
  std::cout << pos << std::endl;
  std::cout << getLastPos() << std::endl;
  std::cout << getDirectionnalVector() << std::endl;
  std::cout << getOppositeDirectionnalVector() << std::endl;
  for (float i = 0; i < length; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      Tile t(pos + getOppositeDirectionnalVector() * j);
      t.add(new Coin(pos + glm::vec3(0.f, 1.f, 0.f) + getOppositeDirectionnalVector() * j, 1, "ruby.obj"));
      _map.push_back(t);
    }
    pos += getDirectionnalVector();
  }
}

glm::vec3 MapManager::getLastPos() const
{
  if (_map.size() == 0)
  {
    return glm::vec3(0.f);
  }
  else
  {
    const Tile &t = *(_map.end() - 3);
    return t.getObjects()[0]->pos();
  }
}

const glm::vec3 &MapManager::getDirectionnalVector() const
{
  switch (_direction)
  {
  case DIR_NORTH:
    return VEC_NORTH;
    break;
  case DIR_SOUTH:
    return VEC_SOUTH;
    break;
  case DIR_EAST:
    return VEC_EAST;
    break;
  case DIR_WEST:
    return VEC_WEST;
    break;
  default:
    throw new Error("Wrong direction : " + std::to_string(_direction), AT);
    break;
  }
}

const glm::vec3 &MapManager::getOppositeDirectionnalVector() const
{
  switch (_direction)
  {
  case DIR_NORTH:
    return VEC_WEST;
    break;
  case DIR_SOUTH:
    return VEC_EAST;
    break;
  case DIR_EAST:
    return VEC_SOUTH;
    break;
  case DIR_WEST:
    return VEC_NORTH;
    break;
  default:
    throw new Error("Wrong direction : " + std::to_string(_direction), AT);
    break;
  }
}
} // namespace UP
