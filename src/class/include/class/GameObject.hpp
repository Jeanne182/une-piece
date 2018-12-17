#ifndef GAME_OBJECT_UP_HPP__
#define GAME_OBJECT_UP_HPP__

#pragma once

#include <vector>
#include <map>

#include <glimac/SDLWindowManager.hpp>
#include <class/Model.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>

using namespace glimac;

namespace UP
{

class GameObject
{
public:
  // ============= CONSTRUCTORS =============
  /**
   * @brief DELETED default constructor
   *
   */
  GameObject() = delete;

  /**
   * @brief Construct a new Game Object object
   *
   * @param pos
   * @param speed
   */
  GameObject(const glm::vec3 &pos, const glm::vec3 &speed, const float &scale, const std::string &name);

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

  // ============= ABSTRACT METHODS =============
  /**
   * @brief Must Implement a way to display the object
   *
   */
  virtual void display() const =0;

  // ============= GETTERS =============
  /**
   * @brief Get the Position object
   *
   * @return glm::vec3
   */
  inline glm::vec3 pos() const { return _position; };

  /**
   * @brief Get the Pos X object
   *
   * @return float
   */
  inline float x() const { return _position[X]; };
  /**
   * @brief Get the Pos Y object
   *
   * @return float
   */
  inline float y() const { return _position[Y]; };
  /**
   * @brief Get the Pos Z object
   *
   * @return float
   */
  inline float z() const { return _position[Z]; };

  /**
   * @brief Get the Speed object
   *
   * @return glm::vec3
   */
  inline glm::vec3 speed() const { return _speed; };
  /**
   * @brief Get the Speed X object
   *
   * @return float
   */
  inline float speedX() const { return _speed[X]; };
  /**
   * @brief Get the Speed Y object
   *
   * @return float
   */
  inline float speedY() const { return _speed[Y]; };
  /**
   * @brief Get the Speed Z object
   *
   * @return float
   */
  inline float speedZ() const { return _speed[Z]; };

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
   * @brief Add the Position object
   *
   * @param position
   */
  inline void addPosition(const glm::vec3 &position) { _position += position; };
  /**
   * @brief Add the Pos X object
   *
   * @param x
   */
  inline void addPosX(const float &x) { _position[X] += x; };
  /**
   * @brief Add the Pos Y object
   *
   * @param y
   */
  inline void addPosY(const float &y) { _position[Y] += y; };
  /**
   * @brief Add the Pos Z object
   *
   * @param z
   */
  inline void addPosZ(const float &z) { _position[Z] += z; };

  /**
   * @brief Set the Speed object
   *
   * @param speed
   */
  inline void setSpeed(const glm::vec3 &speed) { _speed = speed; };

  // ============= METHODS =============
  /**
   * @brief Reset the game object to default
   *
   */
  void reset();


  // ============= MATRIX =============
  /**
   * @brief Compute the MVP and Normal matrix and send them to the GPU
   *
   * @param assetProgram
   * @param cameraMV
   */
  void sendMatrix(const glm::mat4 &cameraMV);


protected:
  float _scale;
  glm::vec3 _position;
  glm::vec3 _speed;
  const std::string _name;
  const Model *_model;
};

} // namespace UP

#endif
