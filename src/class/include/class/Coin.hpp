#ifndef COIN_UP_HPP__
#define COIN_UP_HPP__

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>

#include <class/GameObject.hpp>

using namespace glimac;

namespace UP
{

class Coin : public GameObject
{
public:
  // ============= CONSTRUCTORS =============

  /**
   * @brief Construct a new Coin object
   *
   */
  Coin(const glm::vec3 position, const unsigned int value, const std::string &name);

  /**
   * @brief Destroy the Coin object
   *
   */
  ~Coin(){};

  // ============= GETTERS =============
  /**
   * @brief Get the Value object
   *
   * @return unsigned int
   */
  inline unsigned int value() const { return _value; };

  // ============= SETTERS =============
  /**
   * @brief Set the Rotate Offset object
   *
   * @param r
   */
  inline void setRotateOffset(const float &r)
  {
    _M = glm::rotate(_M, glm::radians(r), glm::vec3(0.f, 1.f, 0.f));
  };

  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */
  bool collisionHandler(GameObject *gameObject);

  /**
   * @brief Rotate the coin
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);

private:
  unsigned int _value;
  float _rotateOffset;
};

} // namespace UP

#endif
