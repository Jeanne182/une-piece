#include <cmath>
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
glm::mat4 Camera::lookAt(const glm::vec3 &pos) const
{
  return glm::lookAt(_position,
                     pos,
                     _upVector);
}

} // namespace glimac