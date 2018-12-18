#ifndef WATER_UP_HPP__
#define WATER_UP_HPP__

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <class/GameObject.hpp>
#include <class/Character.hpp>


using namespace glimac;

namespace UP
{

class Water : public GameObject
{
public:
  // ============= CONSTRUCTORS =============

  /**
   * @brief Construct a new Water object
   *
   */
  Water(const glm::vec3 position);

  /**
   * @brief Destroy the Water object
   *
   */
  ~Water(){};

  /**
   * @brief Display the obstacle
   *
   */
  void display() const;

  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */
  void collisionHandler(GameObject *gameObject);


private:

};

} // namespace UP

#endif
