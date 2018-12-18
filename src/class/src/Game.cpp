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
    : _character("bateau.obj"){};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
  _camera.event(e);
}
void Game::update()
{
  _camera.update();
  //_character.move();
  _character.sendMatrix(_camera.getViewMatrix());
}
void Game::display() const
{
  AssetManager::Get()->assetProgram()._Program.use();
  _character.display();
}

void Game::reset()
{
  _character.reset();
}

}; // namespace UP
