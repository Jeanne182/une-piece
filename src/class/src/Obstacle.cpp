#include <class/Obstacle.hpp>
#include <class/Character.hpp>
#include <class/Utils.hpp>

using namespace glimac;

namespace UP
{

Obstacle::Obstacle(const glm::vec3 position, const std::string &name)
    : GameObject(position,
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.5f,
                 name)
{
  if (name == "tentacle.obj")
  {
    //float x = Utils::dicef(-40.f, 40.f);
    float y = Utils::dicef(0.f, 360.f);
    float z = Utils::dicef(-40.f, 40.f);
    setScale(Utils::dicef(0.1f, 0.35f));
    setAngles(glm::vec3(0.f, y, z));
  }
  else if (name == "rock.obj")
  {
    float y = Utils::dicef(0.f, 360.f);
    setAngles(glm::vec3(0.f, y, 0.f));
    setScale(1.f);
  }
  setMatrix();
}

void Obstacle::computeMatrix(const glm::mat4 &cameraView)
{
  if (_name == "tentacle.obj")
  {
    float tick = SDL_GetTicks() * TENTACLE_ANGLE_SPEED;
    float angleC = cosf(glm::radians(tick)) * TENTACLE_ANGLE_AMPLITUDE;
    float angleS = sinf(glm::radians(tick)) * TENTACLE_ANGLE_AMPLITUDE;
    _M = glm::rotate(_M, glm::radians(-angleC), glm::vec3(0.f, 0.f, 1.f));
    _M = glm::rotate(_M, glm::radians(angleS), glm::vec3(1.f, 0.f, 0.f));
  }
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

bool Obstacle::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character *>(gameObject)->loseHealth(1);
  return false;
}

} // namespace UP
