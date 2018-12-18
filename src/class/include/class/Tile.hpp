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
  Tile(GameObject *gameObject);
  void add(GameObject *gameObject);
  void setMatrix(const glm::mat4 &cameraMV) const;
  void display() const;
  ~Tile(){};
private:

  std::vector<GameObject*> _tileObjects;

};

} // namespace UP

#endif
