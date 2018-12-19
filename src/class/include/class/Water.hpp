#ifndef WATER_UP_HPP__
#define WATER_UP_HPP__

#pragma once

#include <class/GameObject.hpp>

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
  Water(const glm::vec3 position, const bool &forkSection = false);

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
  bool collisionHandler(GameObject *gameObject);

  bool isFork() const { return _forkSection; };

private:
  bool _forkSection;
};

} // namespace UP

#endif
