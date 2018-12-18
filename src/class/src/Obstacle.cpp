#include <map>

#include <glimac/SDLWindowManager.hpp>

#include <class/Obstacle.hpp>

using namespace glimac;

namespace UP
{

Obstacle::Obstacle(const glm::vec3 position, const std::string &name)
    : GameObject(position,
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f,
                 name){};


void Obstacle::display() const
{
  _model->draw();
  //std::cout << _position << std::endl;
}

void Obstacle::collisionHandler(GameObject *gameObject)
{
   dynamic_cast<Character*>(gameObject)->loseHealth(1);
}

} // namespace UP
