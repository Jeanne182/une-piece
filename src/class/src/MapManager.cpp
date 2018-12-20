#include <vector>

#include <class/MapManager.hpp>
#include <class/AssetManager.hpp>
#include <class/Tile.hpp>
#include <class/Program.hpp>
#include <class/Coin.hpp>
#include <class/Obstacle.hpp>
#include <class/Utils.hpp>
#include <class/common.hpp>
#include <class/Water.hpp>

using namespace glimac;

namespace UP
{
// WTF
const float MapManager::P_FLOATING_COINS = 0.5f;

MapManager::MapManager()
    : _direction(DIR_NORTH),
      _probability(10),
      _lastPos(glm::vec3(0.f))
{
  _probability[BATCH_TYPE_SIMPLE] = 2;
  _probability[BATCH_TYPE_COIN] = 3;
  _probability[BATCH_TYPE_OBSTACLE] = 3;
  _probability.shrink_to_fit();

  Utils::setSeed();
  generateSimpleBatch();
  generateSimpleBatch();
  generateSimpleBatch();
  generateSimpleBatch();
  generatePath();
  generateFork();
}

void MapManager::computeMatrix(const glm::mat4 &cameraMV) const
{
  std::deque<Tile>::const_iterator it;
  for (it = _map.cbegin(); it != _map.cend(); ++it)
  {
    (*it).computeMatrix(cameraMV);
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
Tile &MapManager::getTile(const size_t x, const size_t z)
{
  for (int i = 0; i < _map.size(); i++)
  {
    if (_map[i].x() == x && _map[i].z() == z)
      return _map[i];
  }
  throw Error("There is no tile at [" + std::to_string(x) + " , y, " + std::to_string(z) + "]", AT);
};

const Tile &MapManager::getTile(const size_t x, const size_t z) const
{
  return getTile(x, z);
}

void MapManager::updateLastPos(const float &length)
{
  _lastPos = getLastPos() + getDirectionnalVector() * (length - 1);
}

void MapManager::generatePath()
{
  int batchCount = Utils::dicei(MapManager::PATH_SIZE_MIN, MapManager::PATH_SIZE_MAX);
  for (int i = 0; i < batchCount; i++)
  {
    generateBatch();
  }
  generateSimpleBatch();
  generateSimpleBatch();
  generateFork();
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
    //std::cout << "BATCH_TYPE_SIMPLE" << std::endl;
    generateSimpleBatch();
    break;
  case BATCH_TYPE_COIN:
    //std::cout << "BATCH_TYPE_COIN" << std::endl;
    generateCoinBatch();
    break;
  case BATCH_TYPE_OBSTACLE:
    //std::cout << "BATCH_TYPE_OBSTACLE" << std::endl;
    generateObstacleBatch();
    break;
  default:
    //std::cout << "DEFAULT" << std::endl;
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
      float k = j - MapManager::HALF_ROW_SIZE;
      Tile t(pos + getOppositeDirectionnalVector() * k);

      // Put rocks on the side
      sideRocks(j, k, pos, t);
      _map.push_back(t);
    }
    pos += getDirectionnalVector();
  }
  updateLastPos(length);
}

void MapManager::generateCoinBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  int lane = Utils::dicei(MapManager::LANE_MIN, MapManager::LANE_MAX);
  bool floatingCoins = Utils::maybe(MapManager::P_FLOATING_COINS);
  for (float i = 0; i < length - 1; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - MapManager::HALF_ROW_SIZE;
      Tile t(pos + getOppositeDirectionnalVector() * k);

      // Choose the lane
      if (k == lane)
      {
        // Put the rubies in the air
        float y = 0.5f;
        if (floatingCoins && i != 0 && i != length - 2)
        {
          y = 1.5f;
        }
        t.add(new Coin(pos + glm::vec3(0.f, y, 0.f) + getOppositeDirectionnalVector() * k, 1, "ruby.obj"));
      }

      // Put rocks on the side
      sideRocks(j, k, pos, t);
      _map.push_back(t);
    }
    pos += getDirectionnalVector();
  }
  updateLastPos(length);
}

void MapManager::generateObstacleBatch()
{
  int length = Utils::rBatchSize();
  glm::vec3 pos = getLastPos() + getDirectionnalVector();
  int lane = Utils::dicei(MapManager::LANE_MIN, MapManager::LANE_MAX);
  for (float i = 0; i < length - 1; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - MapManager::HALF_ROW_SIZE;
      Tile t(pos + getOppositeDirectionnalVector() * k);

      // Choose the lane
      if (k == lane && i != 0 && i != length - 2)
      {
        t.add(new Obstacle(pos + glm::vec3(0.f, -0.2f, 0.f) + getOppositeDirectionnalVector() * k, "tentacle.obj"));
      }
      // Put rocks on the side
      sideRocks(j, k, pos, t);
      _map.push_back(t);
    }
    pos += getDirectionnalVector();
  }
  updateLastPos(length);
}

void MapManager::generateFork()
{
  // Middle
  glm::vec3 advance = getLastPos() + getDirectionnalVector() * (float)MapManager::HALF_ROW_SIZE;

  // Left Side
  glm::vec3 leftSide = advance + getOppositeDirectionnalVector() * (float)MapManager::HALF_FORK_SIZE;

  glm::vec3 pos = leftSide;

  int noRockMin = MapManager::HALF_FORK_SIZE - MapManager::HALF_ROW_SIZE;
  int noRockMax = MapManager::HALF_FORK_SIZE + MapManager::HALF_ROW_SIZE;
  // Build
  for (float i = 0; i < MapManager::FORK_SIZE; i++)
  {
    for (float j = 0; j < MapManager::ROW_SIZE; j++)
    {
      float k = j - MapManager::HALF_ROW_SIZE;
      Tile t(new Water(pos + getDirectionnalVector() * k, true));


      // Rocks on the side
      if ((j == 0 && (i < noRockMin || i > noRockMax)) ||
          j == MapManager::ROW_SIZE - 1)
      {
        t.add(new Obstacle(pos + glm::vec3(0.f, -0.2f, 0.f) + getDirectionnalVector() * k, "rock.obj"));
      }
      _map.push_back(t);
    }
    pos += getOppositeDirectionnalVector() * -1.f;
  }

  if (getDirectionnalVector()[Z] != 0.f)
  {
    _forks.push_back(pos + getOppositeDirectionnalVector());
    _forks.push_back(leftSide);
  }
  else
  {
    _forks.push_back(leftSide);
    _forks.push_back(pos + getOppositeDirectionnalVector());
  }
}

void MapManager::sideRocks(const float j, const float k, const glm::vec3 &pos, Tile &t)
{

  if ((j == 0 || j == MapManager::ROW_SIZE - 1) && (int)pos[X] % 2 == 0)
  {
    t.add(new Obstacle(pos + glm::vec3(0.f, 0.0f, 0.f) + getOppositeDirectionnalVector() * k, "rock.obj"));
  }
}

void MapManager::selectLeftFork()
{
  _lastPos = _forks[LEFT];
  turnLeft();
  _forks.clear();
}
void MapManager::selectRightFork()
{
  _lastPos = _forks[RIGHT];
  turnRight();
  _forks.clear();
}

void MapManager::deleteOldPath()
{
  bool forkFound = false;
  int cpt = 0;
  // Delete until a forkWater is found
  Water *w = dynamic_cast<Water*>(_map.begin()->object(0));
  while (!(w->isFork()) && cpt < 1000)
  {
    cpt++;
    _map.pop_front();
    w = dynamic_cast<Water*>((_map.begin())->object(0));
  }

  // Delete until a not for Water is found
  while (w->isFork() && cpt < 1000)
  {
    cpt++;
    _map.pop_front();
    w = dynamic_cast<Water*>((_map.begin())->object(0));
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
  case DIR_EAST: /**
   * @brief Destroy elements that are no longer in the game
   *
   */
    void destroy();
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
