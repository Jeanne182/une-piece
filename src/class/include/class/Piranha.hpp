#ifndef PIRANHA_UP_HPP__
#define PIRANHA_UP_HPP__

#pragma once

#include <iostream>

#include <glimac/common.hpp>

#include <class/GameObject.hpp>
#include <class/Character.hpp>

using namespace glimac;

namespace UP
{

class Piranha : public GameObject
{

public:
  /**
   * @brief Construct a new Piranha object
   *
   */
  Piranha(const Character &character);

  /**
   * @brief Destroy the Piranha object
   *
   */
  ~Piranha(){};

  /**
   * @brief Update the position and the rotation of the piranha
   * 
   */
  void update();

  void display() const;
  /**
   * @brief Must Implement a way to handle the behaviour of the collision
   *
   */
  bool collisionHandler(GameObject *gameObject)
  {
    return false;
  };

  /**
   *
   * @brief Compute the MV , MVP and Normal
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);

private:
  const Character &_character;
};

} // namespace UP
#endif