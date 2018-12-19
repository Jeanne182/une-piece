#ifndef GAME_UP_HPP__
#define GAME_UP_HPP__

#pragma once

#include <vector>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <class/Program.hpp>
#include <class/Character.hpp>
#include <class/MapManager.hpp>
#include <class/Camera.hpp>
#include <class/Light.hpp>

using namespace glimac;

namespace UP
{

class Game
{
public:
  /**
   * @brief Construct a new Game object
   *
   * @param appPath
   * @param assetProgram
   */
  Game();
  /**
   * @brief Update all the states of the game
   *
   */
  void update();
  /**
   * @brief Draw the current frame of the game
   *
   */
  void display() const;
  /**
   * @brief Destroy elements that are no longer in the game
   *
   */
  void destroy();
  /**
   * @brief React to a SDL_Event
   *
   * @param e
   */
  void event(const SDL_Event &e);

  /**
   * @brief Reset the game and create a new one
   *
   */
  void reset();
  void collide();

private:
  Character _character;
  Camera _camera;
  Light _light;
  MapManager *_map;
};

} // namespace UP

#endif
