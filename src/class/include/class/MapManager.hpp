#ifndef MAP_MANAGER_UP_HPP__
#define MAP_MANAGER_UP_HPP__

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <class/Tile.hpp>

using namespace glimac;
namespace UP
{

class MapManager
{

public:
  MapManager();

  /**
   * @brief Getter for the map object
   *
   * @return std::vector<Tile>&
   */
  inline std::vector<Tile> &map() { return _map; };
  /**
   * @brief Getter for the map object
   *
   * @return const std::vector<Tile>&
   */
  inline const std::vector<Tile> &map() const { return _map; };

  /**
   * @brief Getter for a tile
   *
   * @param i
   * @param j
   * @return Tile
   */
  Tile operator()(const size_t i, const size_t j) { return _map[i * 3 + j]; };

  /**
   * @brief Getter for a tile
   *
   * @param i
   * @param j
   * @return const Tile
   */
  const Tile operator()(const size_t i, const size_t j) const { return _map[i * 3 + j]; };

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

private:
  std::vector<Tile> _map;
};

} // namespace UP

#endif
