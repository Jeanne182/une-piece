#include <vector>

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>

#include <class/Game.hpp>
#include <class/AssetManager.hpp>
#include <class/Character.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>
#include <class/Light.hpp>
#include <class/Utils.hpp>
#include <class/Water.hpp>

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
        _map->generatePath();
        _map->generateFork();
        _map->selectLeftFork();
        _map->generateBatch();
        _map->deleteOldPath();
        _camera.setCenter(_map->getLastPos());
      }
      if (e.key.keysym.sym == SDLK_t)
      {
        _map->generatePath();
        _map->generateFork();
        _map->selectRightFork();
        _map->generateBatch();
        _map->deleteOldPath();
        _camera.setCenter(_map->getLastPos());
      }
      if (e.key.keysym.sym == SDLK_g)
      {
        _map->generatePath();
        _map->generateFork();
        if (Utils::maybe(0.5f))
          _map->selectRightFork();
        else
          _map->selectLeftFork();
        _map->generateBatch();
        _map->deleteOldPath();
        _camera.setCenter(_map->getLastPos());
      }
    }
  }
}
void Game::update()
{

  // Change Light Direction
  glm::mat4 r = glm::rotate(glm::mat4(1.f), glm::radians(0.01f), glm::vec3(0.f, 1.f, 0.f));
  _light.setDirection(r * _light.direction());

  // Update the scene
  _camera.setCenter(_character.pos());
  _character.move();
  collide();

  // Update the matrixes
  _character.setMatrix();
  _character.computeMatrix(_camera.getViewMatrix());
  _map->computeMatrix(_camera.getViewMatrix());
}

void Game::display() const
{

  // Display stuff
  sendLight();
  _character.display();
  _map->display();
}

void Game::sendLight() const
{
  const AssetProgramMultiLight &a = AssetManager::Get()->assetProgramMultiLight();

  // Compute the V * Light
  glm::vec4 l = _camera.getViewMatrix() * _light.direction();

  // Send it
  a._Program.use();
  glUniform3fv(a.uLightDir_vs, 1, glm::value_ptr(glm::vec3(l)));
  glUniform3fv(a.uLightIntensity, 1, glm::value_ptr(_light.intensity()));
}

void Game::reset()
{
  _character.reset();
  _camera.setCenter(glm::vec3(0.f));
  delete _map;
  _map = new MapManager;
}

void Game::collide()
{
  const std::vector<int> &v = _character.getLastCoordinate();
  int x = Utils::cast(_character.x());
  int y = Utils::cast(_character.y());
  int z = Utils::cast(_character.z());
  if (v[X] != x ||
      v[Y] != y ||
      v[Z] != z)
  {
    //std::cout << "Ancienne position du character : [" << v[X] << "," << v[Y] << "," << v[Z] << "]" << std::endl;
    //std::cout << "Nouvelle position du character : [" << x << "," << y << "," << z << "]" << std::endl;
    //std::cout << "Position du character : " << _character.pos() << std::endl;
    //std::cout << std::endl;
    _character.setLastCoordinate(std::vector<int>{x, y, z});
    _character.cubeCountIncrease();
    Tile &t = _map->getTile(x, z);
    for (int i = 0; i < t.tile().size(); i++)
    {

      // Check if there is a water that is a fork
      Water *w = dynamic_cast<Water *>(t.object(i));
      if (w && w->isFork())
      {
        if (_character.getSideState() == LEFT)
        {
          _map->selectLeftFork();
        }
        else if (_character.getSideState() == RIGHT)
        {
          _map->selectRightFork();
        }
        else
        {
          std::cout << "GAME OVER" << std::endl;
          exit(0);
        }
      }

          t.object(i)->markDeleted();
      //std::cout << "Position de l'objet : " << t.object(i)->pos() << std::endl;
      if (Utils::cast(t.object(i)->y()) == y)
      {
        if (t.object(i)->collisionHandler(&_character))
        {
          t.object(i)->markDeleted();
        }
      }
    }
    t.clean();
  }
}

}; // namespace UP
