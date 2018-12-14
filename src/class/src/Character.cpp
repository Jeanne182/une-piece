#include <class/Character.hpp>

namespace UP
{
Character::Character()
    : _position(0.f, 0.f, 0.f),
      _speed(0.0025f, 0.000025f, 0.0025f),
      _health(1),
      _sideState(CENTER),
      _verticalState(RUNNING)
{
}

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
  switch (_sideState)
  {
  case CENTER:
    sideMove(CENTER);
    break;
  case LEFT:
    sideMove(LEFT);
    break;
  case RIGHT:
    sideMove(RIGHT);
    break;
  }

  switch (_verticalState)
  {
  case RUNNING:
    verticalMove(RUNNING);
    break;
  case SLIDING:
    verticalMove(SLIDING);
    break;
  case JUMPING:
    verticalMove(JUMPING);
    break;
  }
}

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
void Character::addBonus(const Bonus bonus)
{
  time_t startingTime = time(NULL);
  std::map<unsigned int, time_t>::iterator it;
  it = _activeBonuses.find(bonus.getBonusType());
  if(it == _activeBonuses.end())
  {
    useBonus(bonus.getBonusType(), startingTime);
  }
  else
  {
    it->second = startingTime;
  }
}
void Character::deleteConsumedBonus(const Bonus bonus)
{
  std::map<unsigned int, time_t>::iterator it;
  for(it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    if( (it->first) == bonus.getBonusType() )
    {
      _activeBonuses.erase(it);
      break;
    }
  }
}

void Character::deleteExpiredBonuses()
{
  time_t currentTime = time(NULL);
  std::map<unsigned int, time_t>::iterator it;
  for(it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    int expirationTime = (it->second) + BONUS_DURATION;
    if( currentTime == expirationTime ){
      _activeBonuses.erase(it);
    }
  }
}
} // namespace UP
