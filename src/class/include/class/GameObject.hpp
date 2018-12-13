#ifndef GAME_OBJECT_UP_HPP__
#define GAME_OBJECT_UP_HPP__

#pragma once

#include <vector>
#include <map>

#include <glimac/SDLWindowManager.hpp>
#include <class/common.hpp>

using namespace glimac;

namespace UP
{

class GameObject
{
public:
  // ============= CONSTRUCTORS =============
  /**
   * @brief Construct a new GameObject object
   * 
   */
  GameObject();

  /**
   * @brief Construct a new Game Object object
   * 
   * @param pos 
   * @param speed 
   */
  GameObject(const glm::vec3 &pos, const glm::vec3 &speed);

  /**
   * @brief Construct a new Game Object object
   * 
   * @param g 
   */
  GameObject(const GameObject &g);

  /**
   * @brief Destroy the GameObject object
   * 
   */
  ~GameObject(){};

  // ============= GETTERS =============
  /**
   * @brief Get the Position object
   * 
   * @return glm::vec3 
   */
  inline glm::vec3 getPosition() const { return _position; };

  /**
   * @brief Get the Pos X object
   * 
   * @return float 
   */
  inline float getPosX() const { return _position[X]; };
  /**
   * @brief Get the Pos Y object
   * 
   * @return float 
   */
  inline float getPosY() const { return _position[Y]; };
  /**
   * @brief Get the Pos Z object
   * 
   * @return float 
   */
  inline float getPosZ() const { return _position[Z]; };

  /**
   * @brief Get the Speed object
   * 
   * @return glm::vec3 
   */
  inline glm::vec3 getSpeed() const { return _speed; };
  /**
   * @brief Get the Speed X object
   * 
   * @return float 
   */
  inline float getSpeedX() const { return _speed[X]; };
  /**
   * @brief Get the Speed Y object
   * 
   * @return float 
   */
  inline float getSpeedY() const { return _speed[Y]; };
  /**
   * @brief Get the Speed Z object
   * 
   * @return float 
   */
  inline float getSpeedZ() const { return _speed[Z]; };

  // ============= SETTERS =============

  /**
   * @brief Set the Position object
   * 
   * @param position 
   */
  inline void setPosition(const glm::vec3 &position) { _position = position; };
  /**
   * @brief Set the Pos X object
   * 
   * @param x 
   */
  inline void setPosX(const float &x) { _position[X] = x; };
  /**
   * @brief Set the Pos Y object
   * 
   * @param y 
   */
  inline void setPosY(const float &y) { _position[Y] = y; };
  /**
   * @brief Set the Pos Z object
   * 
   * @param z 
   */
  inline void setPosZ(const float &z) { _position[Z] = z; };
  /**
   * @brief Set the Speed object
   * 
   * @param speed 
   */
  inline void setSpeed(const glm::vec3 &speed) { _speed = speed; };

protected:
  glm::vec3 _position;
  glm::vec3 _speed;
};

} // namespace UP

#endif
