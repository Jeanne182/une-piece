#ifndef MAP_MANAGER_UP_HPP__
#define MAP_MANAGER_UP_HPP__

#pragma once

#include <string>
#include <deque>
#include <iostream>

#include <glimac/glm.hpp>

#include <class/Tile.hpp>
#include <class/Error.hpp>

using namespace glimac;
namespace UP
{

class MapManager
{

public:
  // =============== CONSTS FOR THE GENERATION ===============

  static const int ROW_SIZE = 13;
  static const int BATCH_SIZE_MIN = 4;
  static const int BATCH_SIZE_MAX = 7;

  enum BATCH_TYPE : unsigned int
  {
    BATCH_TYPE_SIMPLE,
    BATCH_TYPE_COIN,
    BATCH_TYPE_OBSTACLE
  };

  // =============== CONSTRUCTOR ===============
  /**
   * @brief Construct a new Map Manager object
   *
   */
  MapManager();

  // =============== GETTERS  ===============
  /**
   * @brief Getter for the map object
   *
   * @return std::deque<Tile>&
   */
  inline std::deque<Tile> &map() { return _map; };
  /**
   * @brief Getter for the map object
   *
   * @return const std::deque<Tile>&
   */
  inline const std::deque<Tile> &map() const { return _map; };

  /**
   * @brief Getter for a tile
   *
   * @param i
   * @param j
   * @return Tile
   */
  Tile &getTile(const size_t i, const size_t j);

  /**
   * @brief Getter for a tile
   *
   * @param i
   * @param j
   * @return const Tile
   */
  const Tile& getTile(const size_t i, const size_t j) const;

  /**
   * @brief Get the Pos of the last object
   *
   * @return float
   */
  glm::vec3 getLastPos() const;

  /**
   * @brief Get the Directionnal Vector object
   *
   * @return const glm::vec3&
   */
  const glm::vec3 &getDirectionnalVector() const;

  /**
   * @brief Get the Opposite Directionnal Vector object
   *
   * @return const glm::vec3&
   */
  const glm::vec3 &getOppositeDirectionnalVector() const;
  // =============== METHODS  ===============
  /**
   * @brief Display the Map
   *
   */
  void display() const;

  /**
   * @brief Compute the MVP and Normal matrix and send them to the GPU
   *
   * @param assetProgram
   * @param cameraMV
   */
  void setMatrix(const glm::mat4 &cameraMV) const;

  void generateBatch();
  void generateSimpleBatch();
  void generateCoinBatch();
  void generateObstacleBatch();

  inline void turnRight() { _direction = (_direction + 1) % 4; }
  inline void turnLeft() { _direction = (_direction - 1) % 4; }

private:
  std::deque<Tile> _map;
  std::vector<uint> _probability;
  unsigned int _direction;
};

} // namespace UP

#endif
