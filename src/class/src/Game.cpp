#include <vector>
#include <exception>
#include <typeinfo>

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>

#include <class/Game.hpp>
#include <class/AssetManager.hpp>
#include <class/Character.hpp>
#include <class/ScoresManager.hpp>
#include <class/Score.hpp>
#include <class/Program.hpp>
#include <class/common.hpp>
#include <class/Light.hpp>
#include <class/Utils.hpp>
#include <class/Water.hpp>

using namespace glimac;
namespace UP
{

Game::Game()
    : _character(_camera),
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
  if (_character.health() <= 0)
  {
    gameOver();
  }
  _gameTick++;
  // Acceleration
  if (_gameTick > _nextTickAcceleration)
  {
    std::cout << SDL_GetTicks() << std::endl;
    _nextTickAcceleration += PLAYER_ACCELERATION_INTERVAL;
    _character.speedUp();
  }

  // Update the scene
  _character.move();
  collide();
  _camera.update(_character.pos());

  // Update the matrixes
  _character.updateMatrix();
  _character.computeMatrix(_camera.getViewMatrix());
  _map->computeMatrix(_camera.getViewMatrix());
  _skybox.computeMatrix(_camera.getViewMatrix());

  //gameOver();
}

void Game::display() const
{

  // Display stuff
  sendLight();
  if (_camera.getPOV() != FIRST_PERSON)
    _character.display();
  _map->display();
  _skybox.display();
}

void Game::sendLight() const
{
  const AssetProgramMultiLight &a = AssetManager::Get()->assetProgramMultiLight();

  // Compute the V * Light
  glm::mat4 lightMatrix = glm::transpose(_camera.getViewMatrix());
  glm::vec4 lightVector = glm::normalize(lightMatrix * _light.direction());

  // Send it
  a._Program.use();
  glUniform3fv(a.uLightDir_vs, 1, glm::value_ptr(glm::vec3(lightVector)));
  glUniform3fv(a.uLightIntensity, 1, glm::value_ptr(_light.intensity()));
}

void Game::reset()
{
  // Reset the character
  (&_character)->~Character();
  new (&_character) Character(_camera);
  Character::MAX_SPEED = 0.1f;

  // Reset the camera
  (&_camera)->~Camera();
  new (&_camera) Camera();
  _camera.setCharacterInfo(_character.getScale(), _character.getAngles());

  // Reset the map
  delete _map;
  _map = new MapManager;
}

void Game::gameOver()
{
  if (_gameOverTrigger)
  {
    _gameOverTrigger(_character.score());
  }
  else
  {
    throw Error("No game over trigger", AT);
  }
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

    _character.setLastCoordinate(std::vector<int>{x, y, z});
    _character.cubeCountIncrease();

    Tile &t = _map->getTile(x, z);
    bool shallClean = false;
    for (int i = 0; i < t.tile().size(); i++)
    {

      // Check if there is a water that is a fork
      try
      {
        Water &w = dynamic_cast<Water &>(t.object(i));
        if (w.isFork()) // Water is fork
        {
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
              gameOver();
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
      catch (const std::bad_cast &e)
      {
        // Not a water
        //std::cout << "Position de l'objet : " << t.object(i)->pos() << std::endl;
        // Normal collision handler for something different than water

        /*
        std::cout << "Ancienne position du character : [" << v[X] << "," << v[Y] << "," << v[Z] << "]" << std::endl;
        std::cout << "Nouvelle position du character : [" << x << "," << y << "," << z << "]" << std::endl;
        std::cout << "Position du character : " << _character.pos() << std::endl;
        std::cout << "Position Y de l'obj : " << Utils::cast(t.object(i).y()) << std::endl;
        std::cout << std::endl;
        */

        if (Utils::cast(t.object(i).y()) == y)
        {
          if (t.object(i).collisionHandler(&_character))
          {
            shallClean = true;
            t.object(i).markDeleted();
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
