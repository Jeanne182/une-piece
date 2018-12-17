#include <cstdlib>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/Bonus.hpp>

namespace UP
{
Bonus::Bonus(const glm::vec3 position, const unsigned int bonusType, const std::string &path, const std::map<std::string, GLint> &textureLocation)
    : GameObject(glm::vec3(0.f, 0.f, 0.f),
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f, path, textureLocation),
      _bonusType(bonusType),
      _bonusDuration(BONUS_DURATION){};

void Bonus::display() const
{
  // TODO
}

} // namespace UP
