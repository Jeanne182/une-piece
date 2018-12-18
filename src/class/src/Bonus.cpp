#include <cstdlib>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/Bonus.hpp>
#include <class/Character.hpp>

namespace UP
{
Bonus::Bonus(const glm::vec3 position, const unsigned int bonusType, const std::string &name)
    : GameObject(position,
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.1f,
                 name),
      _bonusType(bonusType),
      _bonusDuration(BONUS_DURATION){};

void Bonus::display() const
{
  useMatrix();
  _model->draw();
}

void Bonus::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character*>(gameObject)->addBonus(*this);
}

} // namespace UP
