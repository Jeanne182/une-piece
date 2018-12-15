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
      _character(appPath.dirPath() + "../../src/assets/models/bateau.obj", assetProgram.uMapTextures)
{
};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
}
void Game::update()
{
  _character.move();
}
void Game::display() const
{
  _character.display(_camera.getViewMatrix(), _assetProgram);
}

}; // namespace UP