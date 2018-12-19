#include <map>

#include <glimac/SDLWindowManager.hpp>

#include <class/Water.hpp>

using namespace glimac;

namespace UP
{

Water::Water(const glm::vec3 position)
    : GameObject(position,
                 glm::vec3(0.f, 0.f, 0.f),
                 1.f,
                 "water.obj"){};


void Water::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

bool Water::collisionHandler(GameObject *gameObject)
{
  return false;
}

} // namespace UP
