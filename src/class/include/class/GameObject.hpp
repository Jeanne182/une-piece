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
   * @param scale 
   * @param name 
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
  void display() const;

  /**
   * @brief Must Implement a way to handle the behaviour of the collision
   *
   */
  virtual bool collisionHandler(GameObject *gameObject) = 0;

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
   * @brief Set the Rotation Angle object
   *
   * @param angles
   */
  inline void setAngles(const glm::vec3 &angles) { _angles = angles; };

  /**
   * @brief Set the Scale object
   *
   * @param scale
   */
  inline void setScale(const float &scale) { _scale = scale; };

  /**
   * @brief Set the Speed object
   *
   * @param speed
   */
  inline void setSpeed(const glm::vec3 &speed) { _speed = speed; };

  // ============= METHODS =============
  /**
   * @brief Utils for the deletion
   * 
   */
  inline void markDeleted() { _toDelete = true; };

  /**
   * @brief Utils for the deletion
   * 
   * @return true 
   * @return false 
   */
  inline bool shallDelete() { return _toDelete; }

  // ============= MATRIX =============
  /**
   * @brief Compute the M and P
   *
   */
  void setMatrix();

  /**
   * @brief Compute the MV , MVP and Normal
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);

  /**
   * @brief Send the matrix to the GPU
   *
   */
  void useMatrix() const;

protected:
  float _scale;
  bool _toDelete = false;
  glm::vec3 _angles;
  glm::vec3 _position;
  glm::vec3 _speed;

  glm::mat4 _P, _M, _N, _MV, _MVP;
  const std::string _name;
  Model *_model;
};

} // namespace UP

#endif