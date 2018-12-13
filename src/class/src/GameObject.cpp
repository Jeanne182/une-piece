#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>

namespace UP
{
GameObject::GameObject()
    : _position(0.f, 0.f, 0.f),
      _speed(0.0025f, 0.000025f, 0.0025f){};

GameObject::GameObject(const glm::vec3 &pos, const glm::vec3 &speed)
    : _position(pos),
      _speed(speed){};

GameObject::GameObject(const GameObject &g)
    : _position(g._position),
      _speed(g._speed){};
} // namespace UP
