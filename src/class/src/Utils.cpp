#include <random>
#include <functional>

#include <class/Utils.hpp>
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

int cast(const float f) {
    return f < 0 ? (int)f - 1 : f;
}

} // namespace Utils
