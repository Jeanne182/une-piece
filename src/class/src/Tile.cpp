#include <glimac/SDLWindowManager.hpp>

#include <class/Tile.hpp>

using namespace glimac;

namespace UP
{

Tile::Tile(const GameObject *gameObject)
{
  _tileObjects.push_back(gameObject);
}


} // namespace UP
