#include <map>

#include <glimac/SDLWindowManager.hpp>

#include <class/Coin.hpp>
#include <class/Character.hpp>

using namespace glimac;

namespace UP
{
Coin::Coin(const glm::vec3 position, const unsigned int value, const std::string &name)
    : GameObject(position,
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f,
                 name),
      _value(value){};

void Coin::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

bool Coin::collisionHandler(GameObject *gameObject)
{
   dynamic_cast<Character*>(gameObject)->addCoin(_value);
   return true;
}

} // namespace UP
