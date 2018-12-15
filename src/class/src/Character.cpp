#include <class/Character.hpp>
#include <class/Model.hpp>

using namespace glimac;

namespace UP
{

Character::Character(const std::string &path, const std::map<std::string, GLint> &textureLocation)
    : GameObject(),
      _health(1),
      _sideState(CENTER),
      _verticalState(RUNNING),
      _model(path, textureLocation),
      _modelMatrix(glm::translate(glm::mat4(1), glm::vec3(1, -3, -5)))
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
  _position += glm::vec3(0, _speed[X], 0);
}

void Character::move()
{
  forwardMove();
  sideMove(_sideState);
  sideMove(_verticalState);
}

void Character::sideMove(const int &side)
{
  switch (side)
  {
  case CENTER:
    if (_position[Y] < 0)
      setPosY(_position[Y] + _speed[Y]);
    else if (_position[Y] > 0)
      setPosY(_position[Y] - _speed[Y]);
    break;
  case LEFT:
    if (_position[Y] > -2)
      setPosY(_position[Y] - _speed[Y]);
    break;
  case RIGHT:
    if (_position[Y] < 2)
      setPosY(_position[Y] + _speed[Y]);
    break;
  }
}

void Character::verticalMove(const int &movement)
{
  switch (movement)
  {
  case RUNNING:
    if (_position[Z] < 0)
      setPosZ(_position[Z] + _speed[Z]);
    else if (_position[Z] > 0)
      setPosZ(_position[Z] - _speed[Z]);
    break;
  case JUMPING:
    if (_position[Z] < 2)
      setPosZ(_position[Z] + _speed[Z]);
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

bool Character::collision(const Character &p2)
{
  if ((int)_position[X] == (int)p2._position[X] && (int)_position[Y] == (int)p2._position[Y] && (int)_position[Z] == (int)p2._position[Z])
  {
    loseHealth(1);
  }
}

void Character::loseHealth(const unsigned int &value)
{
  setHealth(_health - value);
}

glm::mat3 translate(const float tx, const float ty)
{
  return glm::mat3(
      glm::vec3(1, 0, 0),
      glm::vec3(0, 1, 0),
      glm::vec3(tx, ty, 1));
}
glm::mat3 scale(const float sx, const float sy)
{
  return glm::mat3(
      glm::vec3(sx, 0, 0),
      glm::vec3(0, sy, 0),
      glm::vec3(0, 0, 1));
}
glm::mat3 rotate(const float a)
{
  return glm::mat3(
      glm::vec3(cos(a), sin(a), 0),
      glm::vec3(-sin(a), cos(a), 0),
      glm::vec3(0, 0, 1));
}

void Character::display() const
{
  /*
  MVMatrix = glm::scale(glm::translate(glm::mat4(), glm::vec3(0, -3, -5)), glm::vec3(0.3));
  MVMatrix = glm::rotate(MVMatrix,
                         windowManager.getTime() / 2,
                         glm::vec3(0.f, 1.f, 0.f));
  MVMatrix = glm::scale(MVMatrix, glm::vec3(1.0f));
  */

  /* 9_ Envoi des matrices au GPU */
  /*
  glUniformMatrix4fv(assetProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(assetProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(assetProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  assetProgram._Program.use();
  player._model.draw();
  */
}
void Character::display(const glm::mat4 &ProjMatrix, const glm::mat4 &MVMatrix, const glm::mat4 &NormalMatrix, const AssetProgram &assetProgram) const
{
  /*
  MVMatrix = glm::scale(glm::translate(glm::mat4(), glm::vec3(0, -3, -5)), glm::vec3(0.3));
  MVMatrix = glm::rotate(MVMatrix,
                         windowManager.getTime() / 2,
                         glm::vec3(0.f, 1.f, 0.f));
  MVMatrix = glm::scale(MVMatrix, glm::vec3(1.0f));
  */

  /* 9_ Envoi des matrices au GPU */
  glUniformMatrix4fv(assetProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
  glUniformMatrix4fv(assetProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(assetProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

  assetProgram._Program.use();
  _model.draw();
}

} // namespace UP
