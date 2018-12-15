#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/common.hpp>

namespace UP
{
GameObject::GameObject()
    : _position(0.f, 0.f, 0.f),
      _speed(0.f, 0.f, 0.f),
      _scale(1.f){};

GameObject::GameObject(const glm::vec3 &pos, const glm::vec3 &speed, const float &scale)
    : _position(pos),
      _speed(speed),
      _scale(scale){};

GameObject::GameObject(const GameObject &g)
    : _position(g._position),
      _speed(g._speed),
      _scale(g._scale){};

void GameObject::computeMatrix()
{
  _MVMatrix = glm::mat4(1.f);
  _MVMatrix = glm::scale(_MVMatrix, glm::vec3(_scale));
  _MVMatrix = glm::translate(_MVMatrix, glm::vec3(x(), y(), z()));
  _NormalMatrix = glm::transpose(glm::inverse(_MVMatrix));

  /*
  std::cout << "MATRIXES : " << std::endl;
  std::cout << _position << std::endl;
  std::cout << _MVMatrix << _NormalMatrix << std::endl;
  */
}
} // namespace UP
