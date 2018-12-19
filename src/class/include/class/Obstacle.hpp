#ifndef OBSTACLE_UP_HPP__
#define OBSTACLE_UP_HPP__

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

class Obstacle : public GameObject
{
public:
  // ============= CONSTRUCTORS =============

  /**
   * @brief Construct a new Obstacle object
   *
   */
  Obstacle(const glm::vec3 position, const std::string &name);

  /**
   * @brief Destroy the Obstacle object
   *
   */
  ~Obstacle(){};

  /**
   * @brief Display the obstacle
   *
   */
  void display() const;

  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */
  bool collisionHandler(GameObject *gameObject);


private:

};

} // namespace UP

#endif
