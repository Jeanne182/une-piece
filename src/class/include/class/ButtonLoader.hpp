#ifndef BUTTON_LOADER_UP_HPP__
#define BUTTON_LOADER_UP_HPP__

#pragma once

#include <class/StaticImageLoader.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream>

using namespace glimac;

namespace UP
{  

class ButtonLoader : public StaticImageLoader
{
public:
  /// Constructor and destructor
  
  /**
   * @brief Construct a new Button Loader:: Button Loader object
   * DO NOT USE 
   */
  ButtonLoader();

  /**
   * @brief Construct a new Button Loader:: Button Loader object
   * 
   * @param appPath 
   */
  ButtonLoader(const FilePath &appPath);
  
  /**
   * @brief Destroy the Button Loader:: Button Loader object
   * 
   */
  ~ButtonLoader();
  
  /// Methods
  void mouseHover(const SDL_Event &e);
  
};
  
}

#endif 