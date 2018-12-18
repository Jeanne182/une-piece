#include <vector>

#include <class/MapManager.hpp>
#include <class/AssetManager.hpp>
#include <class/Tile.hpp>
#include <class/Program.hpp>
#include <class/Coin.hpp>
#include <class/Obstacle.hpp>
#include <class/Utils.hpp>
#include <class/common.hpp>

using namespace glimac;

namespace UP
{
MapManager::MapManager()
    : _direction(DIR_NORTH),
      _probability(100)
{
  _probability[BATCH_TYPE_SIMPLE] = 2;
  _probability[BATCH_TYPE_COIN] = 3;
  _probability[BATCH_TYPE_OBSTACLE] = 3;
  _probability.shrink_to_fit();

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

  // Generate a random choice between the min and max given
  int p_sum = 0;
  for (size_t i = 0; i < _probability.size(); i++)
    p_sum += _probability[i];
  int r = Utils::dicei(1, p_sum);

  // We look what choice was made
  int choice;
  p_sum = 0;
  for (size_t i = 0; i < _probability.size(); i++)
  {
    p_sum += _probability[i];
    if (p_sum >= r)
    {
      choice = i;
      break;
    }
  }

  // We call the corresponding function
  switch (choice)
  {
  case BATCH_TYPE_SIMPLE:
    std::cout << "BATCH_TYPE_SIMPLE" << std::endl;
    generateSimpleBatch();
    break;
  case BATCH_TYPE_COIN:
    std::cout << "BATCH_TYPE_COIN" << std::endl;
    generateCoinBatch();
    break;
  case BATCH_TYPE_OBSTACLE:
    std::cout << "BATCH_TYPE_OBSTACLE" << std::endl;
    generateObstacleBatch();
    break;
  default:
    std::cout << "DEFAULT" << std::endl;
    generateSimpleBatch();
  }
}

void MapManager::generateSimpleBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  for (float i = 0; i < length - 1; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - 1;
      _map.push_back(Tile(pos + getOppositeDirectionnalVector() * k));
    }
    pos += getDirectionnalVector();
  }
}

void MapManager::generateCoinBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  int lane = Utils::dicei(-1, 1);
  bool floatingCoins = Utils::maybe(0.5f);
  for (float i = 0; i < length - 1; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - 1;
      Tile t(pos + getOppositeDirectionnalVector() * k);

      // Choose the lane
      if (k == lane)
      {
        // Put the rubies in the air
        float y = 1.0f;
        if (floatingCoins && i != 0 && i != length - 2)
        {
          y = 2.0f;
        }
        t.add(new Coin(pos + glm::vec3(0.f, y, 0.f) + getOppositeDirectionnalVector() * k, 1, "ruby.obj"));
      }
      _map.push_back(t);
    }
    pos += getDirectionnalVector();
  }
}

void MapManager::generateObstacleBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  int lane = Utils::dicei(-1, 1);
  for (float i = 0; i < length - 1; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - 1;
      Tile t(pos + getOppositeDirectionnalVector() * k);

      // Choose the lane
      if (k == lane && i != 0 && i != length - 2)
      {
        t.add(new Obstacle(pos + glm::vec3(0.f, -0.2f, 0.f) + getOppositeDirectionnalVector() * k, "tentacle.obj"));
      }
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
    const Tile &t = *(_map.end() - 2);
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
