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
   * @brief Get the std::vector tileObject
   * 
   * @return std::vector<GameObject *> 
   */
  std::vector<GameObject *> tile() const { return _tileObjects; }

  /**
   * @brief Get the gameObject at the given index
   * 
   * @param index 
   * @return GameObject* 
   */
  GameObject *object(const unsigned int index) const;

  const int x() const { return _x; };
  const int z() const { return _z; };

  /**
   * @brief Add a gameObject to the tile
   * 
   * @param gameObject 
   */
  void add(GameObject *gameObject);

  /**
   * @brief Destroy the tile
   * 
   * @param index 
   */
  void destroy(const unsigned int index);

  /**
   * @brief Utils : Call the setMatrix of all GameObjects
   * 
   * @param cameraMV 
   */
  void setMatrix(const glm::mat4 &cameraMV) const;

  /**
   * @brief Delete all the markedAsDelete gameObjects
   * 
   */
  void clean();

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
  int _x, _z;
};

} // namespace UP

#endif
