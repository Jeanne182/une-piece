#include <map>
#include <iostream>

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
      _value(value)
{
  _model->setRepeat(1.f);
};

void Coin::computeMatrix(const glm::mat4 &cameraView)
{
  _M = glm::rotate(_M, glm::radians(COIN_ROTATION_SPEED), glm::vec3(0.f, 1.f, 0.f));
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

bool Coin::collisionHandler(GameObject *gameObject)
{
  dynamic_cast<Character *>(gameObject)->addCoin(_value);
  return true;
}

} // namespace UP
