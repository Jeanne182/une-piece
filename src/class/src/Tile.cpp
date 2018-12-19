#include <glimac/SDLWindowManager.hpp>

#include <class/Tile.hpp>
#include <class/AssetManager.hpp>
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

GameObject *Tile::object(const unsigned int index) const
{
  if (index < _tileObjects.size())
    return _tileObjects[index];
};

void Tile::add(GameObject *gameObject)
{
  _tileObjects.push_back(gameObject);
}

void Tile::destroy(const unsigned int index)
{
  //delete _tileObjects[index];
  //_tileObjects.erase(_tileObjects.begin()+index);
  _tileObjects.clear();
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

void Tile::setMatrix(const glm::mat4 &cameraMV) const
{
  for (int i = 0; i < _tileObjects.size(); i++)
  {
    _tileObjects[i]->setMatrix(cameraMV);
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
