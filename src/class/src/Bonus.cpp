#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include "../include/class/Bonus.hpp"

namespace UP
{

  Bonus::Bonus()
  :_position(0.f,0.f,0.f),
  _currentBonus(NONE,NONE,NONE,NONE)
  {}

  Bonus::Bonus(glm::vec3 position)
  :_position(position),
  _currentBonus(NONE,NONE,NONE,NONE)
  {}

  Bonus::addBonus(const unsigned int bonus){

  }



} // namespace UP
