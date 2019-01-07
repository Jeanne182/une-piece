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

void Bonus::computeMatrix(const glm::mat4 &cameraView)
{
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

bool Bonus::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character*>(gameObject)->addBonus(*this);
  return true;
}

} // namespace UP
