#ifndef MODEL_UP_HPP__
#define MODEL_UP_HPP__

#pragma once

#include <GL/glew.h>
#include <map>
#include <vector>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>

#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>

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
 * @brief Create the GAME Object that serves as a facade for all the OpenGL stuff
 * 
 */
class Game
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
  static Game instance;

  // CONSTRUCTOR
  
  /**
   * @brief Construct a new Game object 
   * 
   * @param appPath 
   * @param width 
   * @param height 
   */
  Game(const FilePath &appPath, const int &width, const int &height)
      : buttons(appPath, width, height),
        staticImages(appPath){};

  // METHODS
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


  // ATTRIBUTES
  int _layout = LAYOUT_DEFAULT;
  ButtonLoader buttons;
  StaticImageLoader staticImages;


  // DELETED
  Game() = delete;
  Game(Game const &) = delete;
  void operator=(Game const &) = delete;

public:

  /**
   * @brief Common Getter for the Singleton's Instance
   * 
   * @param appPath 
   * @param width 
   * @param height 
   * @return Game& 
   */
  static Game &Get(const FilePath &appPath, const int &width, const int &height)
  {
    static Game instance(appPath, width, height);
    return instance;
  };
};

} // namespace UP

#endif