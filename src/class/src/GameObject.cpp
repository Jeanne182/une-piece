#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/AssetManager.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>

namespace UP
{
GameObject::GameObject(const glm::vec3 &pos, const glm::vec3 &speed, const float &scale, const std::string &name)
    : _position(pos),
      _speed(speed),
      _scale(scale),
      _name(name),
      _angles(glm::vec3(0.f)),
      _model(AssetManager::Get()->model(name)){};

GameObject::GameObject(const GameObject &g)
    : _position(g._position),
      _speed(g._speed),
      _scale(g._scale),
      _model(g._model){};

void GameObject::setMatrix(const glm::mat4 &cameraMV)
{
  /* Envoi des matrices au GPU */

  // P
  _P = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.f);

  // MV -> Modify
  _MV = glm::translate(cameraMV, _position);
  _MV = glm::scale(_MV, glm::vec3(_scale));
  _MV = glm::rotate(_MV, glm::radians(_angles[X]), glm::vec3(1.f, 0.f, 0.f));
  _MV = glm::rotate(_MV, glm::radians(_angles[Y]), glm::vec3(0.f, 1.f, 0.f));
  _MV = glm::rotate(_MV, glm::radians(_angles[Z]), glm::vec3(0.f, 0.f, 1.f));

  // Normal
  _N = glm::transpose(glm::inverse(_MV));

  /*
  std::cout << "MVP" << P * MV << std::endl;
  std::cout << "MV" << MV << std::endl;
  std::cout << "Normal" << normalMatrix << std::endl;
*/
}

void GameObject::useMatrix() const
{
  glUniformMatrix4fv(AssetManager::Get()->assetProgram().uMVPMatrix, 1, GL_FALSE, glm::value_ptr(_P * _MV));
  glUniformMatrix4fv(AssetManager::Get()->assetProgram().uMVMatrix, 1, GL_FALSE, glm::value_ptr(_MV));
  glUniformMatrix4fv(AssetManager::Get()->assetProgram().uNormalMatrix, 1, GL_FALSE, glm::value_ptr(_N));
}

void GameObject::reset()
{
  _position = glm::vec3(0.f, 0.f, 0.f);
  _speed = glm::vec3(0.f, 0.f, 0.f);
  _scale = 1.f;
}

} // namespace UP
