#ifndef TILE_UP_HPP__
#define TILE_UP_HPP__

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <class/GameObject.hpp>

using namespace glimac;
namespace UP
{

class Tile
{
public:
  /**
   * @brief Construct a new Tile object
   * 
   * @param position 
   */
  Tile(const glm::vec3 &position);

  /**
   * @brief Construct a new Tile object
   * 
   * @param gameObject 
   */
  Tile(GameObject *gameObject);

  /**
   * @brief Destroy the Tile object
   * 
   */
  ~Tile(){};

  /**
   * @brief Add a new object to the pile
   * 
   * @param gameObject 
   */
  void add(GameObject *gameObject);

  /**
   * @brief Call the setMatrix of all GameObject
   * 
   * @param cameraMV 
   */
  void setMatrix(const glm::mat4 &cameraMV) const;

  /**
   * @brief Call the display of all GameObject
   * 
   */
  void display() const;

  /**
   * @brief 
   * 
   * @return const Tile& 
   */
  inline const std::vector<GameObject *> &getObjects() const { return _tileObjects; };

private:
  std::vector<GameObject *> _tileObjects;
};

} // namespace UP

#endif
