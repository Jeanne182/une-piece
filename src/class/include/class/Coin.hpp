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

  /**
   * @brief Display the Coin
   *
   */
  void display() const;

  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */
  bool collisionHandler(GameObject *gameObject);


private:
  unsigned int _value;
};

} // namespace UP

#endif
