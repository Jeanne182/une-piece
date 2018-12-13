#ifndef CHARACTER_UP_HPP__
#define CHARACTER_UP_HPP__

#pragma once

#include <vector>
#include <map>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>

#include <class/GameObject.hpp>

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

class Character : public GameObject
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
   * @brief Get the Health object
   * 
   * @return unsigned int 
   */
  inline unsigned int getHealth() const { return _health; }

  // ============= SETTERS ============= 
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
