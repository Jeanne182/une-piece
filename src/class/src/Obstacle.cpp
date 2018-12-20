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
  if (name == "tentacle.obj")
  {
    float x = Utils::dicef(-40.f, 40.f);
    float y = Utils::dicef(0.f, 360.f);
    float z = Utils::dicef(-40.f, 40.f);
    setAngles(glm::vec3(x, y, z));
    setScale(Utils::dicef(0.1f, 0.35f));
  }
  else if (name == "hole.obj")
  {
    float y = Utils::dicef(0.f, 360.f);
    setAngles(glm::vec3(0.f, y, 0.f));
    setScale(2.f);
  }
  setMatrix();
}

void Obstacle::display() const
{
  GameObject::display();
}

bool Obstacle::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character *>(gameObject)->loseHealth(1);
  return false;
}

} // namespace UP
