#ifndef BUTTON_LOADER_UP_HPP__
#define BUTTON_LOADER_UP_HPP__

#pragma once

#include <class/StaticImageLoader.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream>

using namespace glimac;

namespace UP
{

enum ButtonState
{
  BUTTON_STATE_BASIC,
  BUTTON_STATE_HOVERED,
  BUTTON_STATE_CLICKED
};

  
struct Button : public StaticImage
{
  GLuint* _texture_hovered;
  GLuint* _texture_clicked;
  bool _isHovered;
  bool _isClicked;
};
  
class ButtonLoader : public StaticImageLoader
{
public:
  /// Constructor and destructor

  /**
   * @brief Construct a new Button Loader:: Button Loader object. Require 3 images : <filename>
   * 
   * @param appPath 
   */
  ButtonLoader(const FilePath &appPath, const int &width, const int &height);
  
  /**
   * @brief Destroy the Button Loader:: Button Loader object
   * 
   */
  ~ButtonLoader();
  
  /// Methods
  
  /**
   * @brief Set the buttons to the state hovered
   *
   */
  void mouseHover(const SDL_Event &e);
  
  /**
   * @brief Set the buttons to the state Clicked
   *
   */
  void mouseClick();  
    
  /**
   * @brief Add an image to the Loader. REQUIRE 3 images : 
   * @brief "<filename>", "<filename>_hovered" and "<filename>_clicked"
   * 
   * @param filename
   * @param x
   * @param y
   * @param scale
   */
  void addImage(const std::string &filename, const float &x=0.f, const float &y=0.f, const float &scale=1.0f);
  
  void setupImage(const std::string &filename, const float &x, const float &y, const float &scale, Button *img);
  
  /**
   * @brief Display 1 image
   * 
   * @param imageName
   */
  void displayImage(const std::string &imageName);
  
private:
  /**
   * @brief Construct a new Button Loader:: Button Loader object
   * DO NOT USE 
   */
  ButtonLoader();
  const int _window_width, _window_height;
};
    
}

#endif 