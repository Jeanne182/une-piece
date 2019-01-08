#include <algorithm>

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
  _tileObjects.push_back(std::unique_ptr<Water> (new Water(position)));
}

Tile::Tile(std::unique_ptr<GameObject> gameObject)
    : _x(Utils::cast(gameObject->x())),
      _z(Utils::cast(gameObject->z()))  
{
  _tileObjects.push_back(std::move(gameObject));
}

void Tile::add(std::unique_ptr<GameObject> gameObject)
{
  if (Utils::cast(gameObject->x()) != _x || Utils::cast(gameObject->z()) != _z)
  {
    throw Error("Trying to add a gameObject to the wrong Tile Coordinates: \n GameObject : " + std::to_string(gameObject->x()) + " , y, " + std::to_string(gameObject->z()) + "\n Tile : " + std::to_string(_x) + ", y, " + std::to_string(_z), AT);
  }
  _tileObjects.push_back(std::move(gameObject));
}

void Tile::clean()
{
 // std::cout << "Size before : " << _tileObjects.size() << std::endl;
  _tileObjects.erase(std::remove_if(_tileObjects.begin(),
                                    _tileObjects.end(),
                                    [](std::unique_ptr<GameObject> &g) { return g->shallDelete(); }),
                     _tileObjects.end());

  //std::cout << "Size After : " << _tileObjects.size() << std::endl;
  //std::cout << std::endl;
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

GameObject& Tile::object(const unsigned int index) const
{
  if (index < _tileObjects.size())
    return *(_tileObjects[index]);
};

} // namespace UP
