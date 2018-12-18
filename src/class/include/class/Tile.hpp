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
<<<<<<< HEAD
  std::vector<const GameObject*> _tileObjects;
=======
  //std::vector<GameObject> _tileObjects;
>>>>>>> 049177a7f985869ded3e288c10b1906bef991172
};

} // namespace UP

#endif
