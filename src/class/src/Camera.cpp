#include <cmath>
#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>

#include <class/Camera.hpp>

namespace glimac
{

const double PI = 3.141592653589;
const double HALF_PI = PI / 2;
Camera::Camera()
    : _position(glm::vec3(0.f, 0.f, 0.f)), _fPhi(PI), _fTheta(0)
{
  computeDirectionVectors();
}

void Camera::event(const SDL_Event &e)
{
  switch (e.type)
  {
  case SDL_KEYDOWN:
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
  break;

  case SDL_KEYUP:
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
  break;

  case SDL_MOUSEMOTION:
  {
    float speed = 0.5f;
    /*
    std::cout << "Mouse move: ";
    std::cout << e.motion.xrel << " | " << e.motion.yrel << std::endl;
    */
    if (e.motion.xrel != 0)
    {
      rotateFront(float(-e.motion.xrel) * speed);
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

void Camera::update()
{
     
    float speed = 0.001f;      
    if (KEY_UP_PRESSED) {
      moveFront(speed);
    } 
    else if (KEY_DOWN_PRESSED) {
      moveFront(-speed);              
    }
    else if (KEY_LEFT_PRESSED) {
      KEY_LEFT_PRESSED = true;
      moveLeft(speed);              
    }
    else if (KEY_RIGHT_PRESSED) {
      KEY_RIGHT_PRESSED = true;
      moveLeft(-speed);              
    }
    
}

void Camera::computeDirectionVectors()
{
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                           std::sin(_fTheta),
                           std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                          0,
                          std::cos(_fPhi + HALF_PI));

  _upVector = glm::cross(_frontVector,
                         _leftVector);
}

void Camera::moveFront(const float &t)
{
  _position += t * _frontVector;
  _upVector = glm::cross(_frontVector,
                         _leftVector);
}
void Camera::moveLeft(const float &t)
{
  _position += t * _leftVector;
  _upVector = glm::cross(_frontVector,
                         _leftVector);
}
void Camera::rotateFront(const float &degrees)
{
  _fPhi += glm::radians(degrees);
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                           std::sin(_fTheta),
                           std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                          0,
                          std::cos(_fPhi + HALF_PI));
}
void Camera::rotateLeft(const float &degrees)
{
  _fTheta += glm::radians(degrees);
  _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                           std::sin(_fTheta),
                           std::cos(_fTheta) * std::cos(_fPhi));

  _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                          0,
                          std::cos(_fPhi + HALF_PI));
}

glm::mat4 Camera::getViewMatrix() const
{
  return glm::lookAt(_position,
                     _position + _frontVector,
                     _upVector);
}
glm::mat4 Camera::look(const glm::vec3 &pos) const
{
  return glm::lookAt(_position,
                     pos,
                     _upVector);
}

} // namespace glimac