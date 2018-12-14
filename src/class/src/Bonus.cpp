#include <cstdlib>
#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <class/Bonus.hpp>

namespace UP
{

  Bonus::Bonus()
  :_position(0.f,0.f,0.f),
  _bonusType(INVULNERABILITY),
  _bonusDuration(BONUS_DURATION)
  {}

  Bonus::Bonus(const glm::vec3 position, const unsigned int bonusType)
  :_position(position),
  _bonusType(bonusType),
  _bonusDuration(BONUS_DURATION)
  {}




} // namespace UP
