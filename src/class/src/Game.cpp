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

  // Change Light Direction
  glm::mat4 r = glm::rotate(glm::mat4(1.f), glm::radians(0.01f), glm::vec3(0.f, 1.f, 0.f));
  _light.setDirection(r * _light.direction());

  // Update the scene
  _camera.update();
  _character.move();
  collide();
  _character.setMatrix(_camera.getViewMatrix());
  _map->setMatrix(_camera.getViewMatrix());
}

void Game::display() const
{
  AssetManager::Get()->assetProgramMultiLight()._Program.use();

  // Compute the ViewMatrix * Light
  glm::vec4 l = _light.direction() * _camera.getViewMatrix();
  //glm::vec4 l = _light.direction();

  // Send it
  const AssetProgramMultiLight &a = AssetManager::Get()->assetProgramMultiLight();
  glUniform3fv(a.uLightDir_vs, 1, glm::value_ptr(glm::vec3(l)));
  glUniform3fv(a.uLightIntensity, 1, glm::value_ptr(_light.intensity()));

  // Display stuff
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

void Game::destroy()
{
  std::deque<Tile> &map = _map->map();
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].tile().size(); j++)
    {
      if (_character.collisionDetector(*(map[i].object(j))) == true)
      {
        std::cout << "Position de l'objet : " << map[i].object(j)->pos() << std::endl;
        std::cout << "Avant d'être supprimer : " << map[i].tile().size() << std::endl;
        map[i].destroy(j);
        for (int k = 0; k < map[i].tile().size(); k++)
        {
          std::cout << "Après la supression : " << map[i].tile().size() << std::endl;
        }
      }
      if (map[i].tile().empty())
      {
        _map->destroy(i);
      }
    }
  }
}

}; // namespace UP
