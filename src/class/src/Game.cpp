#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>

#include <class/Game.hpp>
#include <class/AssetManager.hpp>
#include <class/Character.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>

using namespace glimac;
namespace UP
{

Game::Game()
    : _character(){};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
  _camera.event(e);
}
void Game::update()
{
  _camera.update();
  _character.move();
  destroy();
  _character.setMatrix(_camera.getViewMatrix());
  _map.setMatrix(_camera.getViewMatrix());
}

void Game::display() const
{
  AssetManager::Get()->assetProgram()._Program.use();
  _character.display();
  _map.display();
}

void Game::reset()
{
  _character.reset();
}

void Game::destroy()
{
  std::vector<Tile> map = _map.map();
  for(int i = 0; i < map.size(); i++)
  {
    for(int j = 0; j < map[i].tile().size(); j++)
    {
      if(_character.collisionDetector(*(map[i].object(j))) == true)
      {
        std::cout << "Position de l'objet : " << map[i].object(j)->pos() << std::endl;
        std::cout << "Position du character : " << _character.pos() << std::endl;
        std::cout << "Avant d'être supprimer : " << map[i].tile().size() << std::endl;
        map[i].destroy(j);
        for(int k = 0; k < map[i].tile().size(); k++)
        {
          std::cout << "Après la supression : " << map[i].tile().size() << std::endl;
        }
      }
      if(map[i].tile().empty())
      {
        _map.destroy(i);
      }
    }
  }
}

}; // namespace UP
