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

  /**
   * 
   * @brief Compute the MV , MVP and Normal
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);

  /**
   * @brief Return true if its a fork section
   * 
   * @return true 
   * @return false 
   */
  bool isFork() const { return _forkSection; };

private:
  bool _forkSection;
};

} // namespace UP

#endif
