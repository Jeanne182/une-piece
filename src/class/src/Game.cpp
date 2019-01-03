#include <vector>
#include <exception>
#include <typeinfo>

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
      _map(new MapManager)
{
  _camera.setCharacterInfo(_character.getScale(), _character.getAngles());
};

void Game::event(const SDL_Event &e)
{
  _character.event(e);
  _camera.event(e);
  if (e.type == SDL_KEYDOWN)
  {
    if (e.key.keysym.sym == SDLK_c)
    {
      _camera.setCharacterInfo(_character.getScale(), _character.getAngles());
    }
  }
  if (DEBUG)
  {
    if (e.type == SDL_KEYDOWN)
    {
      if (e.key.keysym.sym == SDLK_r)
      {
        _map->generatePath();
        _map->selectLeftFork();
        _camera.update(_map->getLastPos());
      }
      if (e.key.keysym.sym == SDLK_t)
      {
        _map->generatePath();
        _map->selectRightFork();
        _camera.update(_map->getLastPos());
      }
      if (e.key.keysym.sym == SDLK_g)
      {
        _map->generatePath();
        _map->generateFork();
        if (Utils::maybe(0.5f))
          _map->selectRightFork();
        else
          _map->selectLeftFork();
        _camera.update(_map->getLastPos());
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
  //_character.move();
  collide();
  _camera.update(_character.pos());

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
  _camera.update(glm::vec3(0.f));
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
    bool shallClean = false;
    for (int i = 0; i < t.tile().size(); i++)
    {

      // Check if there is a water that is a fork
      Water *w = dynamic_cast<Water *>(t.object(i));
      //std::cout << w << std::endl;
      if (w != 0)
      {
        if (w->isFork())
        {
          // Water is fork

          if (!_character.getForkSelected())
          {

            // Set the coord when you need to move
            glm::vec3 dirVec = Utils::getDirectionnalVector(_character.getDirection());
            int dirX = static_cast<int>(dirVec[0]) * (MapManager::HALF_ROW_SIZE - 1);
            int dirZ = static_cast<int>(dirVec[2]) * (MapManager::HALF_ROW_SIZE - 1);
            std::vector<int> turnPos = {x + dirX, 0, z + dirZ};

            glm::vec3 opDirVec = Utils::getOppositeDirectionnalVector(_character.getDirection());

            turnPos[X] += opDirVec[X];
            turnPos[Z] += opDirVec[Z];

            std::cout << "Turn pos : " << turnPos[X] << " , " << turnPos[Z] << std::endl;

            _character.setTurnPosition(turnPos);

            // Generate the map
            if (_character.getSideState() == LEFT)
            {
              _character.setTurnChosen(LEFT);
              _map->selectLeftFork();
            }
            else if (_character.getSideState() == RIGHT)
            {
              _character.setTurnChosen(RIGHT);
              _map->selectRightFork();
            }
            else
            {
              std::cout << "GAME OVER" << std::endl;
              exit(0);
            }

            // Modify the player
            _character.setForkSelected(true);

            // Gnererate the map
            _map->generatePath();
            continue;
          }
        }
        // Water is not Fork
        else
        {
          if (_character.getForkSelected())
          {
            _character.setForkSelected(false);
          }
        }
      }
      else
      {
        //std::cout << "Position de l'objet : " << t.object(i)->pos() << std::endl;
        // Normal collision handler for something different than water
        if (Utils::cast(t.object(i)->y()) == y)
        {
          if (t.object(i)->collisionHandler(&_character))
          {
            shallClean = true;
            t.object(i)->markDeleted();
          }
        }
      }
      if (shallClean)
        t.clean();
    }

    // Check if the player must turn
    // The player should turn if he is on a fork
    if ((_character.getDirection() % 2 == 0 && x == _character.getTurnPosition()[X]) ||
        (_character.getDirection() % 2 == 1 && z == _character.getTurnPosition()[Z]))
    {
      // Turn
      if (_character.getTurnChosen() == LEFT)
      {
        _character.turnLeft();
      }
      else if (_character.getTurnChosen() == RIGHT)
      {
        _character.turnRight();
      }
      else
      {
        throw Error("Can't turn on the center", AT);
      }
      _camera.setCharacterInfo(_character.getScale(), _character.getAngles());
    }
  }
}
}; // namespace UP
