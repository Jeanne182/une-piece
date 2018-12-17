#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>

namespace UP
{
GameObject::GameObject(const glm::vec3 &pos, const glm::vec3 &speed, const float &scale, const std::string &path, const std::map<std::string, GLint> &textureLocation)
    : _position(pos),
      _speed(speed),
      _scale(scale),
      _model(path, textureLocation){};

GameObject::GameObject(const GameObject &g)
    : _position(g._position),
      _speed(g._speed),
      _scale(g._scale),
      _model(g._model){};

void GameObject::sendMatrix(const AssetProgram &assetProgram, const glm::mat4 &cameraMV)
{
  /* Envoi des matrices au GPU */

  // P
  glm::mat4 P = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.f);

  // MV -> Modify
  glm::mat4 MV = glm::translate(cameraMV, _position);
  MV = glm::scale(MV, glm::vec3(_scale));

  // Normal
  glm::mat4 normalMatrix = glm::transpose(glm::inverse(MV));

  /*
  std::cout << "MVP" << P * MV << std::endl;
  std::cout << "MV" << MV << std::endl;
  std::cout << "Normal" << normalMatrix << std::endl;
*/
  glUniformMatrix4fv(assetProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(P * MV));
  glUniformMatrix4fv(assetProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MV));
  glUniformMatrix4fv(assetProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void GameObject::reset()
{
  _position = glm::vec3(0.f, 0.f, 0.f);
  _speed = glm::vec3(0.f, 0.f, 0.f);
  _scale = 1.f;
}

} // namespace UP
