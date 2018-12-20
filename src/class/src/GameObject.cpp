#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/GameObject.hpp>
#include <class/AssetManager.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>
#include <class/Utils.hpp>

namespace UP
{
GameObject::GameObject(const glm::vec3 &pos, const glm::vec3 &speed, const float &scale, const std::string &name)
    : _position(pos),
      _speed(speed),
      _scale(scale),
      _name(name),
      _angles(glm::vec3(0.f)),
      _model(AssetManager::Get()->model(name))
{
  setMatrix();
}

GameObject::GameObject(const GameObject &g)
    : _position(g._position),
      _speed(g._speed),
      _scale(g._scale),
      _model(g._model){};

void GameObject::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

void GameObject::setMatrix()
{
  // Compute Matrix

  // P
  _P = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 200.f);

  // MV -> Modify
  _M = glm::translate(glm::mat4(1.f), _position);
  _M = glm::scale(_M, glm::vec3(_scale));
  _M = glm::rotate(_M, glm::radians(_angles[X]), glm::vec3(1.f, 0.f, 0.f));
  _M = glm::rotate(_M, glm::radians(_angles[Y]), glm::vec3(0.f, 1.f, 0.f));
  _M = glm::rotate(_M, glm::radians(_angles[Z]), glm::vec3(0.f, 0.f, 1.f));

  /*
  std::cout << "P" << _P << std::endl;
  std::cout << "M" << _M << std::endl;
*/
}

void GameObject::computeMatrix(const glm::mat4 &cameraView)
{
  _MV = cameraView * _M;
  _MVP = _P * _MV;
  _N = -1.f *glm::transpose(glm::inverse(_MV));
}

void GameObject::useMatrix() const
{
  glUniformMatrix4fv(AssetManager::Get()->assetProgramMultiLight().uMVPMatrix, 1, GL_FALSE, glm::value_ptr(_MVP));
  glUniformMatrix4fv(AssetManager::Get()->assetProgramMultiLight().uMVMatrix, 1, GL_FALSE, glm::value_ptr(_MV));
  glUniformMatrix4fv(AssetManager::Get()->assetProgramMultiLight().uNormalMatrix, 1, GL_FALSE, glm::value_ptr(_N));
}

void GameObject::reset()
{
  _position = glm::vec3(0.f, 0.f, 0.f);
  _speed = glm::vec3(0.f, 0.f, 0.f);
  _scale = 1.f;
}

} // namespace UP
