#include <glimac/SDLWindowManager.hpp>

#include <class/Tile.hpp>
#include <class/AssetManager.hpp>
#include <class/Water.hpp>
#include <class/Utils.hpp>

using namespace glimac;

namespace UP
{

Tile::Tile(const glm::vec3 &position)
    : _x(Utils::cast(position[X])),
      _z(Utils::cast(position[Z]))
{
  _tileObjects.push_back(new Water(position));
}

Tile::Tile(GameObject *gameObject)
    : _x(Utils::cast(gameObject->x())),
      _z(Utils::cast(gameObject->z()))
{
  _tileObjects.push_back(gameObject);
}

GameObject *Tile::object(const unsigned int index) const
{
  if (index < _tileObjects.size())
    return _tileObjects[index];
};

void Tile::add(GameObject *gameObject)
{
  if (Utils::cast(gameObject->x()) != _x || Utils::cast(gameObject->z()) != _z)
  {
    throw Error("Trying to add a gameObject to the wrong Tile Coordinates: \n GameObject : " + std::to_string(gameObject->x()) + " , y, " + std::to_string(gameObject->z()) + "\n Tile : " + std::to_string(_x) + ", y, " + std::to_string(_z), AT);
  }
  _tileObjects.push_back(gameObject);
}

void Tile::clean()
{

  for (int i = 0; i < _tileObjects.size(); i++)
  {
    if (_tileObjects[i]->shallDelete())
    {
      GameObject *g = _tileObjects[i];
      _tileObjects.erase(_tileObjects.begin() + i);
      delete _tileObjects[i];
    }
  }
}

void Tile::computeMatrix(const glm::mat4 &cameraMV) const
{
  for (int i = 0; i < _tileObjects.size(); i++)
  {
    _tileObjects[i]->computeMatrix(cameraMV);
  }
}

void Tile::display() const
{
  for (int i = 0; i < _tileObjects.size(); i++)
  {

    _tileObjects[i]->display();
  }
}

/*Tile::~Tile(){
  for (int i = 0; i < _tileObjects.size(); i++)
  {
    delete _tileObjects[i];
  }
}*/

} // namespace UP
