#include <map>
#include <type_traits>
#include <glm/gtc/noise.hpp>

#include <glimac/SDLWindowManager.hpp>

#include <class/Character.hpp>
#include <class/AssetManager.hpp>
#include <class/Model.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

using namespace glimac;

namespace UP
{
float Character::MAX_SPEED = 0.1f;
const float Character::MAX_JUMP_SPEED = 0.13f;
const glm::vec3 Character::GRAVITY = glm::vec3(0.f, -0.007f, 0.f);
const glm::vec3 Character::JUMP_FORCE = glm::vec3(0.f, MAX_JUMP_SPEED, 0.f);

Character::Character(Camera &camera)
    : GameObject(glm::vec3(0.f, 0.1f, 0.f),
                 glm::vec3(MAX_SPEED, 0.f, 0.f),
                 0.07f,
                 PLAYER_MODEL_NAME),
      _camera(camera),
      _lastCoordinate(3, 0),
      _turnPosition(3, 0),
      _direction(DIR_NORTH),
      _acceleration(0.f),
      _desiredAngle(0.f),
      _health(1),
      _hitFrame(0),
      _forkSelected(false),
      _smoothRotate(false),
      _score(0),
      _cubeCount(0),
      _turnChosen(CENTER),
      _sideState(CENTER),
      _verticalState(RUNNING)
{
  setAngles(glm::vec3(0.f, 90.f, 0.f));
  updateRotScaleMatrix();

  _speed = Utils::getDirectionnalVector(_direction) * MAX_SPEED;
}

void Character::updateRotScaleMatrix()
{
  _rotScaleMatrix = glm::mat4(1.f);
  _rotScaleMatrix = glm::translate(_rotScaleMatrix, glm::vec3(0.f, -0.1f, 0.f));
  _rotScaleMatrix = glm::scale(_rotScaleMatrix, glm::vec3(_scale));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[X]), glm::vec3(1.f, 0.f, 0.f));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[Y]), glm::vec3(0.f, 1.f, 0.f));
  _rotScaleMatrix = glm::rotate(_rotScaleMatrix, glm::radians(_angles[Z]), glm::vec3(0.f, 0.f, 1.f));
}
void Character::updateMatrix()
{
  // MV -> Modify
  float x = glm::perlin(glm::vec2(static_cast<float>(SDL_GetTicks() + 160000) / 1000.f));
  float y = glm::perlin(glm::vec2(static_cast<float>(SDL_GetTicks()) / 3000.f));
  float z = glm::perlin(glm::vec2(static_cast<float>(SDL_GetTicks() + 8000) / 5000.f));
  glm::vec3 displacementVector = glm::vec3(x, y, z) * 0.2f;
  _M = glm::translate(glm::mat4(1.f), _position + displacementVector);
  _M = _M * _rotScaleMatrix;
}

void Character::computeMatrix(const glm::mat4 &cameraView)
{
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

void Character::display() const
{
  if ((_hitFrame / 10) % 2 == 1)
    return;

  //std::cout << "NTM " << std::endl;
  useMatrix();
  bool thereisabonus = bonusIsActive(INVULNERABILITY);

  if (thereisabonus)
  {

    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

    // Render the mesh into the stencil buffer.

    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    _model->draw();

    // Render the thick wireframe version.

    glStencilFunc(GL_NOTEQUAL, 1, -1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    std::map<unsigned int, time_t>::const_iterator it;
    it = _activeBonuses.find(INVULNERABILITY);
    time_t startTime = it->second;
    time_t timeRemaining = startTime + BONUS_DURATION - time(0);

    glLineWidth(3 + timeRemaining);
    glPolygonMode(GL_FRONT, GL_LINE);

    glUniform3fv(AssetManager::Get()->assetProgramMultiLight().uColor, 1, glm::value_ptr(CELL_SHADING_COLOR));
    _model->draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal mode
    glDisable(GL_STENCIL_TEST);
  }
  else
  {
    _model->draw();
  }
}

void Character::event(const SDL_Event &e)
{

  if (_forkSelected)
    return;

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
  if (key == SDLK_RIGHT && _sideState == RIGHT)
  {
    _sideState = CENTER;
  }
  if (key == SDLK_LEFT && _sideState == LEFT)
  {
    _sideState = CENTER;
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

void Character::deleteConsumedBonus(const unsigned int bonusType)
{
  std::map<unsigned int, time_t>::iterator it;
  for (it = _activeBonuses.begin(); it != _activeBonuses.end(); it++)
  {
    if ((it->first) == bonusType)
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
  for (it = _activeBonuses.begin(); it != _activeBonuses.end();)
  {
    int expirationTime = (it->second) + BONUS_DURATION;
    if (currentTime == expirationTime)
    {
      _activeBonuses.erase(it++);
    }
    else
    {
      ++it;
    }
  }
}

void Character::addCoin(const unsigned int &coinValue)
{
  _score += coinValue;
}

void Character::loseHealth(const unsigned int &value)
{
  if (_hitFrame == 0)
  {
    setHealth(_health - value);
    _hitFrame = 100;
  }
}

void Character::gainHealth()
{
  if (_health < 3 )
    setHealth(_health + 1);
}

bool Character::collisionHandler(GameObject *gameObject)
{
  throw Error(std::string("Can't colide with yourself"), AT);
}

void Character::move()
{
  sideMove();

  // Gravity
  if (_verticalState == JUMPING)
    applyForce(GRAVITY);

  //std::cout << "Position :" << _position << std::endl;
  //std::cout << "Speed :" << _speed << std::endl;
  //std::cout << "Acceleration :" << _acceleration << std::endl;
  //std::cout << std::endl;

  //std::cout << "Current Speed : " << glm::length(_speed) << std::endl;

  // Decrease the frame for invul
  if (_hitFrame > 0)
    _hitFrame--;

  // Speed stuff
  speedUpdate();
  if (_position[Y] < 0.1f)
  {
    _position[Y] = 0.1f;
    _speed[Y] = 0.f;
    _verticalState = RUNNING;
  }

  // Angle rotation
  if (_smoothRotate)
  {

    float ratio = 0.05f;

    glm::vec3 rot = _angles * (1.f - ratio);
    setAngles(rot + _desiredAngle * ratio);
    _camera.setCharacterInfo(_scale, _angles);

    updateRotScaleMatrix();

    if (glm::length(_desiredAngle - _angles) < 0.1f)
    {
      setAngles(_desiredAngle);
      _smoothRotate = false;
    }
  }
}

void Character::speedUp()
{
  MAX_SPEED += PLAYER_ACCELERATION_AMOUNT;
  applyForce(Utils::getDirectionnalVector(_direction) * PLAYER_ACCELERATION_AMOUNT);
}

void Character::speedDown()
{
  MAX_SPEED *= PLAYER_DECCELERATION_AMOUNT;
}

void Character::sideMove()
{
  glm::vec3 center = _position * glm::abs(Utils::getDirectionnalVector(_direction));

  if (center[X] == 0.f)
    center[X] = _turnPosition[X];
  if (center[Z] == 0.f)
    center[Z] = _turnPosition[Z];

  glm::vec3 sideDir = Utils::getOppositeDirectionnalVector(_direction);

  if ((_direction % 2) == 1)
  {
    // Debug
    switch (_sideState)
    {
    case CENTER:
      sideDir = sideDir * 0.f;
      break;
    case LEFT:
      sideDir = sideDir * -1.f;
      break;
    case RIGHT:
      sideDir = sideDir * 1.f;
      break;
    }
    /*
    // Bug on this side
    std::cout << "Center :" << center << std::endl;
    std::cout << "Side  " << sideDir << std::endl;
    std::cout << "Target : " << target << std::endl;
    std::cout << "Position : " << _position << std::endl;
    std::cout << std::endl;
*/
  }
  else
  {
    switch (_sideState)
    {
    case CENTER:
      sideDir = sideDir * 0.f;
      break;
    case LEFT:
      sideDir = sideDir * 1.f;
      break;
    case RIGHT:
      sideDir = sideDir * -1.f;
      break;
    }
  }
  glm::vec3 target = center + sideDir;
  // Normal case
  if (glm::distance(target, _position) > 0.01f)
    seek(target);
}

void Character::speedLimiter(glm::vec3 &speed)
{
  float lx = glm::length(speed[X]);
  float ly = glm::length(speed[Y]);
  float lz = glm::length(speed[Z]);
  if (lx > MAX_SPEED)
    speed[X] = glm::normalize(speed[X]) * MAX_SPEED;
  if (ly > MAX_JUMP_SPEED)
    speed[Y] = glm::normalize(speed[Y]) * MAX_SPEED;
  if (lz > MAX_SPEED)
    speed[Z] = glm::normalize(speed[Z]) * MAX_SPEED;
}

void Character::speedUpdate()
{
  // Update velocity
  if (_acceleration != glm::vec3(0.f))
  {
    _speed += _acceleration;
    speedLimiter(_speed);
  }
  if (_speed == glm::vec3(0.f))
  {
    _speed = Utils::getDirectionnalVector(_direction) * Character::MAX_SPEED;
    std::cout << "Ugly debug :/ " << std::endl;
  }

  // Limit speed
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
  glm::vec3 desired = (target - _position) * Character::MAX_SPEED;

  // Steering = Desired minus velocity
  glm::vec3 steer = desired - _speed;
  speedLimiter(steer); // Limit to maximum steering force
  steer = steer * glm::abs(Utils::getOppositeDirectionnalVector(_direction));
  applyForce(steer);
}

void Character::changeMovement()
{
  _turnChosen = CENTER;

  // Stop the player
  applyForce(_speed * -1.f);

  // Lunch in new dir
  glm::vec3 newDir = Utils::getDirectionnalVector(_direction) * Character::MAX_SPEED;
  std::cout << "New dir : " << newDir << std::endl;

  applyForce(newDir);

  std::cout << "Speed: " << _speed << std::endl;
}

void Character::setForkSelected(const bool &b)
{
  _forkSelected = b;
  if (b)
    _sideState = CENTER;
}

void Character::turnRight()
{
  _direction = (_direction + 1) % 4;
  changeMovement();
  _desiredAngle = glm::vec3(_angles[X], _angles[Y] - 90.f, _angles[Z]);
  _smoothRotate = true;
  updateRotScaleMatrix();
}

void Character::turnLeft()
{
  _direction = (_direction - 1) % 4;
  changeMovement();
  _desiredAngle = glm::vec3(_angles[X], _angles[Y] + 90.f, _angles[Z]);
  _smoothRotate = true;
  updateRotScaleMatrix();
}

bool Character::bonusIsActive(unsigned int bonusType) const
{
  std::map<unsigned int, time_t>::const_iterator it;
  it = _activeBonuses.find(bonusType);
  if (it == _activeBonuses.end())
  {
    return false;
  }
  else
  {
    return true;
  }
}
} // namespace UP
