#ifndef APP_UP_HPP__
#define APP_UP_HPP__

#pragma once

#include <GL/glew.h>
#include <map>
#include <vector>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>

#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>
#include <class/ScoresManager.hpp>
#include <class/Game.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Data Structure for the Layout Modes
 *
 */
enum LAYOUT
{
  LAYOUT_DEFAULT,
  LAYOUT_MENU,
  LAYOUT_SCORES,
  LAYOUT_PAUSE,
  LAYOUT_GAME
};
/**
 * @brief Single Class
 * @brief Create the App Object that serves as a facade for all the OpenGL stuff
 *
 */
class App
{
public:
  // =============== SELECT THE LAYOUT ===============
  /**
   * @brief Use the Layout of the Menu
   *
   */
  void layoutMenu();

  /**
   * @brief Use the Layout of the Scores
   *
   */
  void layoutScores();

  /**
   * @brief Use the Layout of the Pause
   *
   */
  void layoutPause();

  /**
   * @brief Use the Layout of the Game
   *
   */
  void layoutGame();

  // =============== GENERIC FACADES FUNCTIONS ===============
  /**
   * @brief Draw based on the current selected _layout
   *
   */
  void draw();

  /**
   * @brief React to a SDL_Event based on the current selected _layout
   *
   * @param e
   */
  void event(const SDL_Event &e);

private:
  static App instance;

  // CONSTRUCTOR

  /**
   * @brief Construct a new App object
   *
   */
  App();

  // ============ METHODS ============
  /**
   * @brief Setup Opengl to use 2D graphics
   * 
   */
  void layout2D();
  /**
   * @brief Setup Opengl to use 3D graphics
   * 
   */
  void layout3D();

  // ============ SPECIFIC FUNCTIONS FOR EACH LAYOUT ============
  /**
   * @brief Draw the Menu
   *
   */
  void drawMenu();

  /**
   * @brief Draw the Scores
   *
   */
  void drawScores();

  /**
   * @brief Draw the Pause
   *
   */
  void drawPause();

  /**
   * @brief Draw the Game
   *
   */
  void drawGame();

  // ================ ATTRIBUTES ==============


  // Loaders
  ButtonLoader _buttons;
  StaticImageLoader _staticImages;
  Game _game;

  // Internal States
  int _layout = LAYOUT_DEFAULT;

  // ================ SINGLETON's STUFF ==============
  App(App const &) = delete;
  void operator=(App const &) = delete;

public:
  /**
   * @brief Common Getter for the Singleton's Instance
   */
  static App &Get()
  {
    static App instance;
    return instance;
  };
};

} // namespace UP

#endif
