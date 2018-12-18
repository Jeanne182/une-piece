#include <glimac/SDLWindowManager.hpp>

#include <class/Tile.hpp>
#include <class/Water.hpp>

using namespace glimac;

namespace UP
{

Tile::Tile(const glm::vec3 &position)
{
  _tileObjects.push_back(new Water(position));
}

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
