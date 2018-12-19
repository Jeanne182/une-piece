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
  Tile(const glm::vec3 &position);
  Tile(GameObject *gameObject);
  std::vector<GameObject*> tile() const { return _tileObjects; }
  GameObject* object(const unsigned int index) const { if(index < _tileObjects.size()) return _tileObjects[index]; };
  void add(GameObject *gameObject);
  void destroy(const unsigned int index);
  void setMatrix(const glm::mat4 &cameraMV) const;
  void display() const;
  ~Tile(){};
private:

  std::vector<GameObject*> _tileObjects;

};

} // namespace UP

#endif
