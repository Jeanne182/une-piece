#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include <class/Character.hpp>

namespace UP
{
Character::Character()
    : _health(1),
      _sideState(CENTER),
      _verticalState(RUNNING){};

Character::Character(const glm::vec3 &pos, const glm::vec3 &speed)
    : GameObject(pos, speed),
      _health(1),
      _sideState(CENTER),
      _verticalState(RUNNING){};

void Character::display() const
{
  // TODO
};

void Character::keyDownHandler(const int &key)
{
  /* left and right player */
  if (key == SDLK_RIGHT)
  {
    _sideState = RIGHT;
  }
  if (key == SDLK_LEFT)
  {
    _sideState = LEFT;
  }
  /* up and down player */
  if (key == SDLK_UP)
  {
    _verticalState = JUMPING;
  }
  if (key == SDLK_DOWN)
  {
    _verticalState = SLIDING;
  }
}

void Character::keyUpHandler(const int &key)
{
  /* left and right player */
  if (key == SDLK_RIGHT)
  {
    _sideState = CENTER;
  }
  if (key == SDLK_LEFT)
  {
    _sideState = CENTER;
  }
  /* up and down player */
  if (key == SDLK_UP)
  {
    _verticalState = RUNNING;
  }
  if (key == SDLK_DOWN)
  {
    _verticalState = RUNNING;
  }
}

void Character::forwardMove()
{
  _position += glm::vec3(0, _speed[X], 0);
}

void Character::move()
{
  forwardMove();
  sideMove(_sideState);
  verticalMove(_verticalState);
}
// 1-epsilon * posOùjesuis
// SI posOùjesuis < epsilon tp à 0
void Character::sideMove(const int &side)
{
  switch (side)
  {
  case CENTER:
    if (_position[Y] < 0)
    {
      setPosY(_position[Y] + _speed[Y]);
    }
    if (_position[Y] > 0)
    {
      setPosY(_position[Y] - _speed[Y]);
    }
    break;
  case LEFT:
    if (_position[Y] > -2)
    {
      setPosY(_position[Y] - _speed[Y]);
    }
    break;
  case RIGHT:
    if (_position[Y] < 2)
    {
      setPosY(_position[Y] + _speed[Y]);
    }
    break;
  }
}

void Character::verticalMove(const int &movement)
{
  switch (movement)
  {
  case RUNNING:
    if (_position[Z] < 0)
    {
      setPosZ(_position[Z] + _speed[Z]);
    }
    if (_position[Z] > 0)
    {
      setPosZ(_position[Z] - _speed[Z]);
    }
    break;
  case SLIDING:
    if (_position[Z] > -2)
    {
      setPosZ(_position[Z] - _speed[Z]);
    }
    break;
  case JUMPING:
    if (_position[Z] < 2)
    {
      setPosZ(_position[Z] + _speed[Z]);
    }
    break;
  }
}
} // namespace UP
