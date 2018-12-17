#include <glimac/glm.hpp>

#include <glimac/FilePath.hpp>

#include <class/Game.hpp>
#include <class/Character.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>

using namespace glimac;
namespace UP
{

Game::Game(const FilePath &appPath, const AssetProgram &assetProgram)
    : _appPath(appPath),
      _assetProgram(assetProgram),
      //_character(appPath.dirPath() + "../../src/assets/models/bateau.obj")
      _character("bateau.obj")
{
};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
  _camera.event(e);
}
void Game::update()
{
  _camera.update();
  _character.move();
  _character.sendMatrix(_assetProgram, _camera.getViewMatrix());
}
void Game::display() const
{
  _assetProgram._Program.use();
  _character.display();
}

void Game::reset()
{
  _character.reset();
}

}; // namespace UP
