#ifndef GAME_UP_HPP__
#define GAME_UP_HPP__

#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <class/Program.hpp>
#include <class/Character.hpp>
#include <class/Piranha.hpp>
#include <class/MapManager.hpp>
#include <class/Camera.hpp>
#include <class/Skybox.hpp>
#include <class/Light.hpp>

using namespace glimac;

namespace UP
{

class Game
{
public:
  // ============= CONSTRUCTOR =============
  /**
   * @brief Construct a new Game object
   *
   */
  Game();

  // ============= METHODS =============
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
   * @brief Get the score
   * 
   * @return const int 
   */
  const int score() const { return _character.score(); }

  /**
   * @brief Reset the game and create a new one
   *
   */
  void reset();

  /**
   * @brief  Handle stuff to end the game
   *
   */
  void gameOver();

  /**
   * @brief Set the Game Over Trigger object
   *
   * @param trigger
   */
  inline void setGameOverTrigger(std::function<void(const int &)> &trigger)
  {
    _gameOverTrigger = trigger;
  };

  /**
   * @brief Get the Character object
   * 
   * @return const Character& 
   */
  inline const Character &getCharacter() { return _character; };

private:
  Character _character;
  Piranha _piranha;
  Camera _camera;
  Light _light;
  MapManager *_map;
  Skybox _skybox;
  std::function<void(const int &)> _gameOverTrigger;

  unsigned int _nextTickAcceleration = PLAYER_ACCELERATION_INTERVAL;
  unsigned int _gameTick = 0;

  // ============= METHODS =============
  void sendLight() const;
  void magnetCollide();
  void collide();
};

} // namespace UP

#endif
