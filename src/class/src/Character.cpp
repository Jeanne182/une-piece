#include <map>
#include <type_traits>

#include <glimac/SDLWindowManager.hpp>

#include <class/Character.hpp>
#include <class/AssetManager.hpp>
#include <class/Model.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

using namespace glimac;

namespace UP
{

Character::Character()
    : GameObject(glm::vec3(0.f, 0.1f, 0.f),
                 glm::vec3(0.0001f, 0.0001f, 0.0001f),
                 0.5f,
                 "bateau.obj"),
      _lastCoordinate(3,0),
      _health(1),
      _score(0),
      _sideState(CENTER),
      _verticalState(RUNNING){};

void Character::event(const SDL_Event &e)
{
  switch (e.type)
  {
  case SDL_KEYDOWN:
    /* left/right and up/down player */
    keyDownHandler(e.key.keysym.sym);
    break;

  case SDL_KEYUP:
    /* left/right and up/down player */
    keyUpHandler(e.key.keysym.sym);
    break;
  }
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
  /* up player */
  if (key == SDLK_UP)
  {
    _verticalState = JUMPING;
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
  /* up player */
  if (key == SDLK_UP)
  {
    _verticalState = RUNNING;
  }
}

void Character::forwardMove()
{
  addPosX(speedX());
}

void Character::move()
{
  forwardMove();
  sideMove(_sideState);
  verticalMove(_verticalState);
}

void Character::sideMove(const int &side)
{
  switch (side)
  {
  case CENTER:
    if (_position[Z] < 0)
    {
      setPosY(_position[Z] + _speed[Z]);
    }
    else if (_position[Z] > 0)
    {
      setPosY(_position[Z] - _speed[Z]);
    }
    break;
  case LEFT:
    if (_position[Z] > -2)
    {
      setPosY(_position[Z] - _speed[Z]);
    }
    break;
  case RIGHT:
    if (_position[Z] < 2)
    {
      setPosY(_position[Z] + _speed[Z]);
    }
    break;
  }
}

void Character::verticalMove(const int &movement)
{
  switch (movement)
  {
  case RUNNING:
    if (_position[Y] > 3*_speed[Y])
    {
      setPosZ(_position[Y] - _speed[Y]);
    }
    break;
  case JUMPING:
    if (_position[Y] < 2)
    {
      setPosZ(_position[Y] + _speed[Y]);
    }
    break;
  }
}

void Character::addBonus(const Bonus &bonus)
{
  time_t startingTime = time(NULL);
  std::map<unsigned int, time_t>::iterator it;
  it = _activeBonuses.find(bonus.getBonusType());
  if (it == _activeBonuses.end())
  {
    useBonus(bonus.getBonusType(), startingTime);
  }
  else
  {
    it->second = startingTime;
  }
}

void Character::deleteConsumedBonus(const Bonus &bonus)
{
  std::map<unsigned int, time_t>::iterator it;
  for (it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    if ((it->first) == bonus.getBonusType())
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
  for (it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    int expirationTime = (it->second) + BONUS_DURATION;
    if (currentTime == expirationTime)
    {
      _activeBonuses.erase(it);
    }
  }
}

void Character::addCoin(const unsigned int coinValue)
{
  _score += coinValue;
}
/*
const float epsilon = 0.9f;
if ( abs(cast(_position[X]) - cast(gameObject.x())) < epsilon &&
    abs(cast(_position[Y]) - cast(gameObject.y())) < epsilon &&
    abs(cast(_position[Z]) - cast(gameObject.z())) < epsilon)
*/
bool Character::collisionDetector(GameObject &gameObject)
{
  if ( Utils::cast(_position[X]) == Utils::cast(gameObject.x()) &&
      Utils::cast(_position[Y]) == Utils::cast(gameObject.y()) &&
      Utils::cast(_position[Z]) == Utils::cast(gameObject.z()))
  {
    return gameObject.collisionHandler(this);
  }
  return false;
}

void Character::loseHealth(const unsigned int &value)
{
  setHealth(_health - value);
}

void Character::display() const
{
  useMatrix();
  _model->draw();
  //std::cout << _position << std::endl;
}

void Character::reset()
{
  // Directly Copied from the constructor
  // TAKE CARE
  GameObject::reset();
  _health = 1;
  _sideState = CENTER;
  _verticalState = RUNNING;
  _activeBonuses.clear();
  setSpeed(glm::vec3(0.0001f, 0.0001f, 0.0001f));
  _scale = 1.f;
}

bool Character::collisionHandler(GameObject *gameObject)
{
  throw Error(std::string("Can't colide with yourself"), AT);
}

} // namespace UP
