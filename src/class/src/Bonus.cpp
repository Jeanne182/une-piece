#include <cstdlib>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/Bonus.hpp>

namespace UP
{

Bonus::Bonus()
    : _bonusType(INVULNERABILITY),
      _bonusDuration(BONUS_DURATION){};

Bonus::Bonus(const glm::vec3 position, const unsigned int bonusType)
    : _bonusType(bonusType),
      _bonusDuration(BONUS_DURATION){};

void Bonus::display() const
{
  // TODO
}

} // namespace UP
