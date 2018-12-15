#ifndef MAP_MANAGER_UP_HPP__
#define MAP_MANAGER_UP_HPP__

#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace glimac;
namespace UP
{

class Tile
{
public:
  Tile();

};

class MapManager
{

public:
  MapManager();
  std::vector<Tile> map();
  const std::vector<Tile> map() const;

private:
  std::vector<Tile> _map;
};

} // namespace UP

#endif