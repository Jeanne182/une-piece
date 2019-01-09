#include <cmath>
#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>

#include <class/Camera.hpp>
#include <class/common.hpp>
#include <class/Utils.hpp>

namespace UP
{

const double PI = 3.141592653589;
const double HALF_PI = PI / 2;
const float Camera::VIEW_WIDTH = 30.f;

Camera::Camera()
    : _currentPOV(THIRD_PERSON)
{
  computeDirectionVectors();
};

void Camera::event(const SDL_Event &e)
{

  // Change the point of view
  if (e.type == SDL_KEYDOWN)
  {
    if (e.key.keysym.sym == SDLK_c)
    {
      if (_currentPOV != THIRD_PERSON)
        _currentPOV = THIRD_PERSON;
      else
      {
        _currentPOV = FIRST_PERSON;
        _fTheta = glm::radians(_fAngleX);
        _fPhi = glm::radians(-_fAngleY);
        computeDirectionVectors();
      }
    }
    if (e.key.keysym.sym == SDLK_v && DEBUG)
      _currentPOV = ROTATING;
    if (e.key.keysym.sym == SDLK_b && DEBUG)
      _currentPOV = FREE_FLY;
    //std::cout << "Changement de camera : " << _currentPOV << std::endl;
  }

  // Handle the keys for the rotating camera
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
        TPMoveFront(zoom);
      }
      else if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
      {
        //std::cout << "S or DOWN pressed" << std::endl;
        TPMoveFront(-zoom);
      }
    }
    break;

    case SDL_MOUSEMOTION:
    {
      float speed = 1.f;
      if (e.motion.xrel != 0)
      {
        TPRotateRight(float(e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0)
      {
        TPRotateLeft(float(e.motion.yrel) * speed);
      }
    }
    break;

    default:
      break;
    }
  }
  //Handle the keys for the first person
  else if (_currentPOV == FIRST_PERSON || _currentPOV == FREE_FLY)
  {
    switch (e.type)
    {

      /* Touche clavier DOWN */
    case SDL_KEYDOWN:
    {
      if (_currentPOV == FREE_FLY)
      {
        if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP)
        {
          KEY_UP_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
        {
          KEY_DOWN_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT)
        {
          KEY_LEFT_PRESSED = true;
        }
        if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
        {
          KEY_RIGHT_PRESSED = true;
        }
      }
    }
    break;

    case SDL_KEYUP:
    {
      if (_currentPOV == FREE_FLY)
      {
        if (e.key.keysym.sym == SDLK_z || e.key.keysym.sym == SDLK_UP)
        {
          KEY_UP_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
        {
          KEY_DOWN_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_LEFT)
        {
          KEY_LEFT_PRESSED = false;
        }
        if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
        {
          KEY_RIGHT_PRESSED = false;
        }
      }
    }
    break;

    case SDL_MOUSEMOTION:
    {
      float speed = 0.5f;
      //std::cout << "Mouse move: ";
      //std::cout << e.motion.xrel << " | " << e.motion.yrel << " | Phi: " << _fPhi << " | Theta: " << _fTheta << std::endl;
      if (e.motion.xrel != 0)
      {
        FPRotateFront(float(-e.motion.xrel) * speed);
      }
      if (e.motion.yrel != 0)
      {
        FPRotateLeft(float(e.motion.yrel) * speed);
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
  /* CONTROL */
  if (_currentPOV == FREE_FLY)
  {
    float speed = 0.1f;
    if (KEY_UP_PRESSED)
    {
      FPMoveFront(speed);
    }
    else if (KEY_DOWN_PRESSED)
    {
      FPMoveFront(-speed);
    }
    else if (KEY_LEFT_PRESSED)
    {
      KEY_LEFT_PRESSED = true;
      FPMoveLeft(speed);
    }
    else if (KEY_RIGHT_PRESSED)
    {
      KEY_RIGHT_PRESSED = true;
      FPMoveLeft(-speed);
    }
  }
  else if (_currentPOV == FIRST_PERSON)
  {
    _center = center + glm::vec3(0.f, 0.4f, 0.f);
  }
  else
  {
    _center = center;
  }
}

void Camera::setCharacterInfo(const float &scale, const glm::vec3 &angles)
{
  _fDistance = -5.f;
  _fAngleX = 10.f;
  _fAngleY = -angles[Y];
  _boatAngle = angles;
  _fPhi = glm::radians(-_fAngleY);
  _fTheta = 0.f;
  computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
  if (_currentPOV == FIRST_PERSON || _currentPOV == FREE_FLY)
  {
    return glm::lookAt(_center, _center + _frontVector, _upVector);
  }
  else
  {
    glm::mat4 VM = glm::mat4(1.f);
    VM = glm::translate(VM, glm::vec3(0.0f, 0.0f, _fDistance));
    VM = glm::rotate(VM, glm::radians(_fAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    VM = glm::rotate(VM, glm::radians(_fAngleY + 180.f), glm::vec3(0.0f, 1.0f, 0.0f));
    VM = glm::translate(VM, -_center);
    if (_currentPOV == THIRD_PERSON)
    {
      VM = glm::translate(VM, glm::vec3(0.f, -1.f, 0.f));
    }
    return VM;
  }
}

// ========================== THIRD PERSON ========================
void Camera::TPMoveFront(const float &delta)
{
  if (delta > 0 && _fDistance >= -1.0f)
    return;
  _fDistance += delta;
}
void Camera::TPRotateLeft(const float &degrees)
{
  _fAngleX += degrees;
}
void Camera::TPRotateRight(const float &degrees)
{
  _fAngleY -= degrees;
}

// ========================== FIRST PERSON ========================
void Camera::computeDirectionVectors()
{
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi), std::sin(_fTheta), std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI), 0, std::cos(_fPhi + HALF_PI));

  _upVector = glm::cross(_frontVector, _leftVector);
}

void Camera::FPMoveFront(const float &t)
{
  assert(_currentPOV == FREE_FLY);

  _center += t * _frontVector;
  _upVector = glm::cross(_frontVector, _leftVector);
}
void Camera::FPMoveLeft(const float &t)
{
  assert(_currentPOV == FREE_FLY);

  _center += t * _leftVector;
  _upVector = glm::cross(_frontVector, _leftVector);
}
void Camera::FPRotateFront(const float &degrees)
{
  _fPhi += glm::radians(degrees);
  if (_currentPOV == FIRST_PERSON)
  {
    _fPhi = Utils::clamp(_fPhi, glm::radians(-_fAngleY - Camera::VIEW_WIDTH), glm::radians(-_fAngleY + Camera::VIEW_WIDTH));
  }
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi), std::sin(_fTheta), std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI), 0, std::cos(_fPhi + HALF_PI));
}
void Camera::FPRotateLeft(const float &degrees)
{
  _fTheta += glm::radians(degrees);
  if (_currentPOV == FIRST_PERSON)
  {
    _fTheta = Utils::clamp(_fTheta, glm::radians(-Camera::VIEW_WIDTH), glm::radians(Camera::VIEW_WIDTH));
  }
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi), std::sin(_fTheta), std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI), 0, std::cos(_fPhi + HALF_PI));
}

} // namespace UP