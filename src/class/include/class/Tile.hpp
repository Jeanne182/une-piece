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
  std::vector<GameObject*> tile() const { return _tileObjects; }
  GameObject* object(const unsigned int index) const { return _tileObjects[index]; };
  void add(GameObject *gameObject);
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
