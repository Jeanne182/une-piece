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
   * @param std::unique_ptr<GameObject>
   */
  Tile(std::unique_ptr<GameObject> gameObject);

  /**
   * @brief Get the std::vector tileObject
   *
   * @return std::vector<std::unique_ptr<GameObject>>
   */
  inline std::vector<std::unique_ptr<GameObject>> &tile() { return _tileObjects; }

  inline const std::vector<std::unique_ptr<GameObject>> &tile() const { return _tileObjects; }

  /**
   * @brief Get the gameobject at given index
   * 
   * @param index 
   * @return std::unique_ptr<GameObject> 
   */
  GameObject &object(const unsigned int index) const;

  /**
   * @brief Get x
   * 
   * @return const int 
   */
  const int x() const { return _x; };

  /**
   * @brief Get z
   * 
   * @return const int 
   */
  const int z() const { return _z; };

  /**
   * @brief Add a gameObject to the tile
   *
   * @param gameObject
   */
  void add(std::unique_ptr<GameObject> gameObject);

  /**
   * @brief Utils : Call the computeMatrix of all GameObjects
   *
   * @param cameraMV
   */
  void computeMatrix(const glm::mat4 &cameraMV) const;

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

private:
  std::vector<std::unique_ptr<GameObject>> _tileObjects;
  int _x, _z;
};

} // namespace UP

#endif
