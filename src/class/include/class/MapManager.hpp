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

  static const int ROW_SIZE = 9;
  static const int HALF_ROW_SIZE = (ROW_SIZE - 1) / 2;
  static const int BATCH_SIZE_MIN = 4;
  static const int BATCH_SIZE_MAX = 7;
  static const int PATH_SIZE_MIN = 14;
  static const int PATH_SIZE_MAX = 18;
  static const float P_FLOATING_COINS;
  static const int LANE_MIN = -1;
  static const int LANE_MAX = 1;
  static const int FORK_SIZE = ROW_SIZE * 4;
  static const int HALF_FORK_SIZE = FORK_SIZE / 2;

  enum BATCH_TYPE : unsigned int
  {
    BATCH_TYPE_SIMPLE,
    BATCH_TYPE_COIN,
    BATCH_TYPE_OBSTACLE
  };
  enum FORK_POS_VECTOR
  {
    LEFT,
    RIGHT
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
   * @brief Get the Tile object
   *
   * @param x
   * @param z
   * @return Tile&
   */
  Tile &getTile(const size_t x, const size_t z);

  /**
   * @brief Get the Tile object
   *
   * @param x
   * @param z
   * @return const Tile&
   */
  const Tile &getTile(const size_t x, const size_t z) const;

  /**
   * @brief Get the Pos of the last object
   *
   * @return float
   */
  inline const glm::vec3 &getLastPos() const { return _lastPos; };

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
   * @brief Call the computeMatrix of each Tile
   *
   * @param cameraMV
   */
  void computeMatrix(const glm::mat4 &cameraMV) const;

  /**
   * @brief Delete the already seen Tiles
   *
   */
  void deleteOldPath();

  /**
   * @brief Update the _lastPos Object
   *
   * @param length
   */
  void updateLastPos(const float &length);

  /**
   * @brief Create a bunch of batches
   *
   */
  void generatePath();
  /**
   * @brief Create one of the existing batches
   *
   */
  void generateBatch();
  /**
   * @brief A batch with just water
   *
   */
  void generateSimpleBatch();
  /**
   * @brief A batch with coin
   *
   */
  void generateCoinBatch();
  /**
   * @brief A batch with random obstacle
   *
   */
  void generateObstacleBatch();
  /**
   * @brief A fork in the path
   *
   */
  void generateFork();

  /**
   * @brief Select the Left way of the next fork
   *
   */
  void selectLeftFork();
  /**
   * @brief Select the Left way of the next fork
   *
   */
  void selectRightFork();

private:
  std::deque<Tile> _map;
  std::vector<glm::vec3> _forks;
  std::vector<uint> _probability;
  glm::vec3 _lastPos;
  unsigned int _direction;

  /**
   * @brief Modify the _direction vector to turn right
   *
   */
  inline void turnRight() { _direction = (_direction + 1) % 4; }

  /**
   * @brief Modify the _direction vector to turn left
   *
   */
  inline void turnLeft() { _direction = (_direction - 1) % 4; }


  /**
   * @brief Utils Function to create the rocks on the side
   *
   * @param j
   * @param k
   * @param pos
   * @param t
   */
  void sideRocks(const float j, const float k, const glm::vec3 &pos, Tile &t);
};

} // namespace UP

#endif
