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
    : _character(),
      _map(new MapManager){};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
  _camera.event(e);
  if (DEBUG)
  {
    if (e.type == SDL_KEYDOWN)
    {
      if (e.key.keysym.sym == SDLK_r)
      {
        _map->turnLeft();
      }
      if (e.key.keysym.sym == SDLK_t)
      {
        _map->turnRight();
      }
      if (e.key.keysym.sym == SDLK_g)
      {
        _map->generateBatch();
        _camera.setCenter(_map->getLastPos());
      }
    }
  }
}
void Game::update()
{
  _camera.update();
  //_character.move();
  _character.setMatrix(_camera.getViewMatrix());
  _map->setMatrix(_camera.getViewMatrix());
}
void Game::display() const
{
  AssetManager::Get()->assetProgram()._Program.use();
  _character.display();
  _map->display();
}

void Game::reset()
{
  _character.reset();
  _camera.setCenter(glm::vec3(0.f));
  delete _map;
  _map = new MapManager;
}

}; // namespace UP
