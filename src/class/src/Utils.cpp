#include <random>
#include <cmath>
#include <functional>

#include <class/Utils.hpp>
#include <class/common.hpp>
#include <class/Bonus.hpp>
#include <class/MapManager.hpp>

GLenum glCheckError_(const char *file, int line)
{
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string error;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    case GL_STACK_OVERFLOW:
      error = "STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      error = "STACK_UNDERFLOW";
      break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
  }
  return errorCode;
}

namespace Utils
{

void setSeed()
{
  Utils::seed = std::chrono::system_clock::now().time_since_epoch().count();
}
int dicei(const int min, const int max)
{
  std::uniform_int_distribution<int> uniformIntDistribution(min, max);
  return uniformIntDistribution(generator);
}
float dicef(const float min, const float max)
{
  std::uniform_real_distribution<float> uniformIntDistribution(min, max);
  return uniformIntDistribution(generator);
}
bool maybe(const float p)
{
  std::uniform_real_distribution<float> uniformRealDistribution(0, 1);
  return uniformRealDistribution(generator) < p;
}
int rBatchSize()
{
  std::uniform_int_distribution<int> uniformIntDistribution(
      UP::MapManager::BATCH_SIZE_MIN,
      UP::MapManager::BATCH_SIZE_MAX);
  return uniformIntDistribution(generator);
}

int cast(const float f)
{
  return static_cast<int>(round(f));
}

const glm::vec3 &getDirectionnalVector(const unsigned int &direction)
{
  switch (direction)
  {
  case UP::DIR_NORTH:
    return UP::VEC_NORTH;
    break;
  case UP::DIR_SOUTH:
    return UP::VEC_SOUTH;
    break;
  case UP::DIR_EAST:
    return UP::VEC_EAST;
    break;
  case UP::DIR_WEST:
    return UP::VEC_WEST;
    break;
  default:
    throw new Error("Wrong direction : " + std::to_string(direction), AT);
    break;
  }
}

const glm::vec3 &getOppositeDirectionnalVector(const unsigned int &direction)
{
  switch (direction)
  {
  case UP::DIR_NORTH:
    return UP::VEC_WEST;
    break;
  case UP::DIR_SOUTH:
    return UP::VEC_EAST;
    break;
  case UP::DIR_EAST:
    return UP::VEC_SOUTH;
    break;
  case UP::DIR_WEST:
    return UP::VEC_NORTH;
    break;
  default:
    throw new Error("Wrong direction : " + std::to_string(direction), AT);
    break;
  }
}

const std::string &getBonusModelName(const unsigned int bonusType)
{
  switch (bonusType)
  {
  case UP::INVULNERABILITY:
    return UP::BONUS_INVULNERABILITY_MODEL_NAME;
    break;
  case UP::SLOWNESS:
    return UP::BONUS_SLOWNESS_MODEL_NAME;
    break;
  case UP::LIFEUP:
    return UP::BONUS_LIFEUP_MODEL_NAME;
    break;
  case UP::MAGNET:
    return UP::BONUS_MAGNET_MODEL_NAME;
    break;
  }
}
} // namespace Utils
