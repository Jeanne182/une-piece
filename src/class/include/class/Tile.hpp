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
  Tile();
  Tile(const GameObject *gameObject);
  ~Tile(){};
private:
  std::vector<const GameObject*> _tileObjects;
};

} // namespace UP

#endif
