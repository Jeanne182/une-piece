#include <class/Piranha.hpp>
#include <class/Character.hpp>
#include <class/Utils.hpp>

using namespace glimac;
namespace UP
{

Piranha::Piranha(const Character &character)
    : GameObject(glm::vec3(0.f),
                 glm::vec3(0.f),
                 0.15f,
                 PINRANHA_MODEL_NAME),
      _character(character){};

void Piranha::update(const unsigned int &cosOffset)
{
  // Basic position
  _position = _character.pos();
  _position += Utils::getDirectionnalVector(_character.getDirection()) * -2.f;

  float off = static_cast<float>(cosOffset);
  // Y
  _position[Y] = cos(glm::radians(off * 2)) * 0.1f;

  // Z or X
  float left = sin(glm::radians(off)) * 0.3f;
  float front = cos(glm::radians(off * 2)) * 0.2f;
  _position += Utils::getOppositeDirectionnalVector(_character.getDirection()) * left;
  _position += Utils::getDirectionnalVector(_character.getDirection()) * front;

  _angles = _character.getAngles();
  setMatrix();
}

void Piranha::computeMatrix(const glm::mat4 &cameraView)
{
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

void Piranha::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

} // namespace UP
