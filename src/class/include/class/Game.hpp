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

private:
  Character _character;
  const FilePath &_appPath;
  const AssetProgram &_assetProgram;
  Camera _camera;

  // ================ SINGLETON's STUFF ==============
public:
  /**
   * @brief Common Getter for the Singleton's Instance
   * 
   */
  static Game &Get(const FilePath &appPath, const AssetProgram &assetProgram)
  {
    static Game instance(appPath, assetProgram);
    return instance;
  };

  // DELETED
  Game(Game const &) = delete;
  void operator=(Game const &) = delete;

private:
  // CONSTRUCTOR
  Game(const FilePath &appPath, const AssetProgram &assetProgram);
};

} // namespace UP

#endif