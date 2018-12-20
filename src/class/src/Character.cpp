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
const float Character::MAX_SPEED = 0.01f;
const glm::vec3 Character::GRAVITY = glm::vec3(0.f,-0.00008f, 0.f);
const glm::vec3 Character::JUMP_FORCE = glm::vec3(0.f,0.02f, 0.f);

Character::Character()
    : GameObject(glm::vec3(0.f, 0.1f, 0.f),
                 glm::vec3(0.005f,0.f,0.f),
                 0.3f,
                 "bateau.obj"),
      _lastCoordinate(3, 0),
      _acceleration(0.f),
      _health(1),
      _score(0),
      _cubeCount(0),
      _sideState(CENTER),
      _verticalState(RUNNING)
{
  setAngles(glm::vec3(0.f, 90.f, 0.f));
  _rotScaleMatrix = glm::mat4(1.f);
  _rotScaleMatrix = glm::translate(_rotScaleMatrix, glm::vec3(-0.2f, -0.2f, 0.f));
  _rotScaleMatrix = glm::scale(_rotScaleMatrix, glm::vec3(_scale));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[X]), glm::vec3(1.f, 0.f, 0.f));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[Y]), glm::vec3(0.f, 1.f, 0.f));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[Z]), glm::vec3(0.f, 0.f, 1.f));
}

void Character::setMatrix()
{
  // P
  _P = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 200.f);

  // MV -> Modify
  _M = glm::translate(glm::mat4(1.f), _position);
  _M = _M * _rotScaleMatrix;

  /*
  std::cout << "P" << _P << std::endl;
  std::cout << "M" << _M << std::endl;
*/
}

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
  if (key == SDLK_UP && _verticalState == RUNNING)
  {
    _verticalState = JUMPING;
    applyForce(JUMP_FORCE);
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
}


void Character::sideMove()
{
  switch (_sideState)
  {
  case CENTER:
    seek(glm::vec3(x(), y(), 0.f));
  break;
  case LEFT:
    seek(glm::vec3(x(), y(), -1.f));
  break;
  case RIGHT:
    seek(glm::vec3(x(), y(), 1.f));
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

void Character::addCoin(const unsigned int &coinValue)
{
  _score += coinValue;
}

void Character::loseHealth(const unsigned int &value)
{
  setHealth(_health - value);
}

void Character::display() const
{
  GameObject::display();
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

void Character::forwardMove()
{
  addPosX(speedX());
}

void Character::move()
{
  //forwardMove();
  // Gravity
  sideMove();
  if(_verticalState == JUMPING)
    applyForce(GRAVITY);
  std::cout << "Position :" << _position << std::endl;
  std::cout << "Speed :" << _speed << std::endl;
  std::cout << "Acceleration :" << _acceleration << std::endl;
  std::cout << std::endl;
  speedUpdate();
  if(_position[Y] < 0.01f){
    _position[Y] = 0.01f;
    _speed[Y] = 0.f;
    _verticalState = RUNNING;
  }


}

void Character::speedLimiter(glm::vec3 &speed)
{
  float ly = glm::length(speed[Y]);
  float lz = glm::length(speed[Z]);
  if( ly > MAX_SPEED){
    speed[Y] = glm::normalize(speed[Y]) * MAX_SPEED;
  }
  if( lz > MAX_SPEED){
    speed[Z] = glm::normalize(speed[Z]) * MAX_SPEED;
  }
}

void Character::speedUpdate()
{
   // Update velocity
   _speed += _acceleration;

   // Limit speed
   speedLimiter(_speed);
   _position += _speed;

   _acceleration = glm::vec3(0.f);
 }

void Character::applyForce(const glm::vec3 &force)
{
   _acceleration += force;
}

// A method that calculates a steering force towards a target
  // STEER = DESIRED MINUS VELOCITY
void Character::seek(const glm::vec3 &target)
{
    glm::vec3 desired = target - _position; // A vector pointing from the location to the target

    // Scale to maximum speed
    speedLimiter(desired);

    // Steering = Desired minus velocity
    glm::vec3 steer = desired - _speed;
    speedLimiter(steer); // Limit to maximum steering force
    steer[X] = 0.f;
    steer[Y] = 0.f;
    applyForce(steer);
}

} // namespace UP
