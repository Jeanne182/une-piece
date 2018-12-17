#ifndef GAME_UP_HPP__
#define GAME_UP_HPP__

#pragma once

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <class/Program.hpp>
#include <class/Character.hpp>
#include <class/Camera.hpp>

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
  Game(const FilePath &appPath, const AssetProgram &assetProgram);
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

private:
  Character _character;
  const FilePath &_appPath;
  const AssetProgram &_assetProgram;
  Camera _camera;
};

} // namespace UP

#endif
