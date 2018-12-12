#ifndef CHARACTER_HPP__
#define CHARACTER_HPP__

#pragma once

#include <vector>
#include <map>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>

using namespace glimac;

namespace UP
{

enum SIDE
{
  LEFT,
  CENTER,
  RIGHT
};

enum VERTICAL
{
  SLIDING,
  RUNNING,
  JUMPING
};

enum COORD
{
  Y,
  X,
  Z
};

class Character
{
public:
  // ============= CONSTRUCTORS ============= 
  /**
   * @brief Construct a new Character object
   * 
   */
  Character();

  /**
   * @brief Destroy the Character object
   * 
   */
  ~Character() {}

  // ============= GETTERS ============= 
  /**
   * @brief Get the Position object
   * 
   * @return glm::vec3 
   */
  inline glm::vec3 getPosition() const { return _position; }

  /**
   * @brief Get the Pos X object
   * 
   * @return float 
   */
  inline float getPosX() const { return _position[X]; }
  /**
   * @brief Get the Pos Y object
   * 
   * @return float 
   */
  inline float getPosY() const { return _position[Y]; }
  /**
   * @brief Get the Pos Z object
   * 
   * @return float 
   */
  inline float getPosZ() const { return _position[Z]; }

  /**
   * @brief Get the Speed object
   * 
   * @return glm::vec3 
   */
  inline glm::vec3 getSpeed() const { return _speed; }
  /**
   * @brief Get the Speed X object
   * 
   * @return float 
   */
  inline float getSpeedX() const { return _speed[X]; }
  /**
   * @brief Get the Speed Y object
   * 
   * @return float 
   */
  inline float getSpeedY() const { return _speed[Y]; }
  /**
   * @brief Get the Speed Z object
   * 
   * @return float 
   */
  inline float getSpeedZ() const { return _speed[Z]; }

  /**
   * @brief Get the Health object
   * 
   * @return unsigned int 
   */
  inline unsigned int getHealth() const { return _health; }

  // ============= SETTERS ============= 

  /**
   * @brief Set the Position object
   * 
   * @param position 
   */
  inline void setPosition(const glm::vec3 &position) { _position = position; }
  /**
   * @brief Set the Pos X object
   * 
   * @param x 
   */
  inline void setPosX(const float &x) { _position[X] = x; }
  /**
   * @brief Set the Pos Y object
   * 
   * @param y 
   */
  inline void setPosY(const float &y) { _position[Y] = y; }
  /**
   * @brief Set the Pos Z object
   * 
   * @param z 
   */
  inline void setPosZ(const float &z) { _position[Z] = z; }
  /**
   * @brief Set the Speed object
   * 
   * @param speed 
   */
  inline void setSpeed(const glm::vec3 &speed) { _speed = speed; }
  /**
   * @brief Set the Health object
   * 
   * @param health 
   */
  inline void setHealth(const unsigned int &health) { _health = health; }

  // ============= MOVEMENT ============= 
  /**
   * @brief Handle the Key down SDL event
   * 
   * @param key 
   */
  void keyDownHandler(const int &key);

  /**
   * @brief Handle the Key up SDL event
   * 
   * @param key 
   */
  void keyUpHandler(const int &key);

  /**
   * @brief Manage all the movements of the character
   * 
   */
  void move();

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




  // ============= MOVEMENT ============= 
  /**
   * @brief Constantly make the character move forward
   * 
   */
  void forwardMove();

  /**
   * @brief Move on the side given : LEFT, CENTER, RIGHT
   * 
   * @param side 
   */
  void sideMove(const int &side);

  /**
   * @brief Move on the vertical type given : SLIDING, RUNNING, JUMPING
   * 
   * @param movement 
   */
  void verticalMove(const int &movement);
};

} // namespace UP

#endif
