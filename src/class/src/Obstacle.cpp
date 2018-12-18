#include <class/Obstacle.hpp>
#include <class/Character.hpp>
#include <class/Utils.hpp>

using namespace glimac;

namespace UP
{

Obstacle::Obstacle(const glm::vec3 position, const std::string &name)
    : GameObject(position,
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f,
                 name)
{
  float x = Utils::dicef(-40.f, 40.f);
  float y = Utils::dicef(0.f, 360.f);
  float z = Utils::dicef(-40.f, 40.f);
  setAngles(glm::vec3(x, y, 0.f));
  setScale(Utils::dicef(0.1f, 0.35f));
}

void Obstacle::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

void Obstacle::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character *>(gameObject)->loseHealth(1);
}

} // namespace UP
