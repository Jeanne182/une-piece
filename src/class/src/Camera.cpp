#include <cmath>
#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>

#include <class/Camera.hpp>
#include <class/common.hpp>

namespace UP
{

const double PI = 3.141592653589;
const double HALF_PI = PI / 2;

Camera::Camera()
    : _fDistance(-15.0f),
      _fAngleX(0.0f),
      _fAngleY(0.0f),
      _center(0.f, 0.f, 0.f),
      _currentPOV(THIRD_PERSON)
{
}

void Camera::event(const SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
  {
    if (e.key.keysym.sym == SDLK_c)
    {
      std::cout << "Changement de camera" << std::endl;
      if (_currentPOV != FIRST_PERSON)
        _currentPOV = THIRD_PERSON;
      else
        _currentPOV = FIRST_PERSON;
    }
    if (e.key.keysym.sym == SDLK_v && DEBUG)
      _currentPOV = ROTATING;
  }

  if (_currentPOV == ROTATING)
  {
    switch (e.type)
    {
      /* Touche clavier */
    case SDL_KEYDOWN:
    {
      float zoom = 1.0f;
      if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP)
      {
        //std::cout << "Z or UP pressed" << std::endl;
        moveFront(zoom);
      }
      else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
      {
        //std::cout << "S or DOWN pressed" << std::endl;
        moveFront(-zoom);
      }
    }
    break;

    case SDL_MOUSEMOTION:
    {
      float speed = 1.f;
      if (e.motion.xrel != 0)
      {
        rotateRight(float(e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0)
      {
        rotateLeft(float(e.motion.yrel) * speed);
      }
    }
    break;

    default:
      break;
    }
  }
}

void Camera::update(const glm::vec3 &center)
{
  _center = center;
}

void Camera::setCharacterInfo(const float &scale, const glm::vec3 &angles)
{
  _fDistance = scale * -10.0f;
  _fAngleX = 10.f;
  _fAngleY = -angles[Y];
}

void Camera::moveFront(const float &delta)
{
  if (delta > 0 && _fDistance >= -1.0f)
    return;
  _fDistance += delta;
}
void Camera::rotateLeft(const float &degrees)
{
  _fAngleX += degrees;
}
void Camera::rotateRight(const float &degrees)
{
  _fAngleY += degrees;
}
glm::mat4 Camera::getViewMatrix() const
{
  glm::mat4 VM = glm::mat4(1.f);
  VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, _fDistance));
  VM = glm::rotate(VM, glm::radians(_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
  VM = glm::rotate(VM, glm::radians(_fAngleY+180.f), glm::vec3(0.0f, 1.0f, 0.0f));
  VM = glm::translate(VM, -_center);
  if ( _currentPOV == THIRD_PERSON )
  {
    VM = glm::translate(VM, glm::vec3(0.f, -1.f, 0.f));
  }
  return VM;
}

} // namespace UP