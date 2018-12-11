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
  DEFAULT,
  MENU
};
/**
 * @brief Single Class
 * @brief Create the GAME Object that serves as a facade for all the OpenGL stuff
 * 
 */
class Game
{
public:
  /**
   * @brief Use the Layout of the menu
   * 
   */
  void layoutMenu();

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
  /**
   * @brief Draw the Menu
   * 
   */
  void drawMenu();

  /**
   * @brief React to an event for the menu
   * 
   * @param e 
   */
  void eventMenu(const SDL_Event &e);


  // ATTRIBUTES
  int _layout = DEFAULT;
  ButtonLoader buttons;
  StaticImageLoader staticImages;


  // DELETED
  /**
   * @brief DELETED Game Default Constructor
   * 
   */
  Game() = delete;

  /**
   * @brief DELETED Game object Constructor
   * 
   */
  Game(Game const &) = delete;

  /**
   * @brief DELETED operator =
   * 
   */
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