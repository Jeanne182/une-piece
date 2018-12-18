#include <map>

#include <glimac/SDLWindowManager.hpp>

#include <class/Water.hpp>

using namespace glimac;

namespace UP
{

Water::Water(const glm::vec3 position)
    : GameObject(position,
                 glm::vec3(0.f, 0.f, 0.f),
                 0.5f,
                 "water.obj")
{
  _model->setRepeat(0.2f);
};

void Water::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

void Water::collisionHandler(GameObject *gameObject)
{
  return;
}

} // namespace UP
