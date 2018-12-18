#ifndef OBSTACLE_UP_HPP__
#define OBSTACLE_UP_HPP__

#pragma once

#include <class/GameObject.hpp>

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
   * @brief Display the obstacle
   *
   */
  void display() const;

  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */
  void collisionHandler(GameObject *gameObject);

};

} // namespace UP

#endif
