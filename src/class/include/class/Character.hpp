#ifndef CHARACTER_HPP__
#define CHARACTER_HPP__

#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <vector>
#include <map>
#include <glimac/common.hpp>



namespace UP
{

  enum SIDE {
    LEFT,
    CENTER,
    RIGHT
  };

  enum VERTICAL {
    SLIDING,
    RUNNING,
    JUMPING
  };

  enum COORD {
    Y,
    X,
    Z
  };

class Character
{
public:
  /*  Functions  */
  Character();
  ~Character(){}

  /*  Getters  */
  inline glm::vec3 getPosition() const { return _position; }
  inline float getPosX() const { return _position[X]; }
  inline float getPosY() const { return _position[Y]; }
  inline float getPosZ() const { return _position[Z]; }

  inline glm::vec3 getSpeed() const { return _speed; }
  inline float getSpeedX() const { return _speed[X]; }
  inline float getSpeedY() const { return _speed[Y]; }
  inline float getSpeedZ() const { return _speed[Z]; }

  inline unsigned int getHealth() const { return _health; }

  /*  Setters  */
  inline void setPosition(const glm::vec3 &position){ _position = position; }
  inline void setPosX(const float &x){ _position[X] = x; }
  inline void setPosY(const float &y){ _position[Y] = y; }
  inline void setPosZ(const float &z){ _position[Z] = z; }
  inline void setSpeed(const glm::vec3 &speed){ _speed = speed; }
  inline void setHealth(const unsigned int &health){ _health = health; }

  /*  Movement */
  void keyDownHandler(const int &key);
  void keyUpHandler(const int &key);
  void forwardMove();
  void move();
  void sideMove(const int &side);
  void verticalMove(const int &movement);


private:
  //  Position Data
  glm::vec3 _position;

  // Speed Data
  glm::vec3 _speed;

  // Health data
  unsigned int _health;

  // State data
  int _sideState;
  int _verticalState;
};

} // namespace UP

#endif
