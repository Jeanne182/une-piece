#include <glimac/SDLWindowManager.hpp>

#include <class/Tile.hpp>

using namespace glimac;

namespace UP
{

Tile::Tile(GameObject *gameObject)
{
  _tileObjects.push_back(gameObject);
}

void Tile::add(GameObject *gameObject)
{
  _tileObjects.push_back(gameObject);
}

void Tile::setMatrix(const glm::mat4 &cameraMV) const
{
  for (int i = 0; i < _tileObjects.size(); i++)
  {
    _tileObjects[i]->setMatrix(cameraMV);
  }
}

void Tile::display() const
{
  for (int i = 0; i <   _tileObjects.size(); i++)
  {
    _tileObjects[i]->display();
  }
}

} // namespace UP
