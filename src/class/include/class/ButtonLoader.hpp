#ifndef BUTTON_LOADER_UP_HPP__
#define BUTTON_LOADER_UP_HPP__

#pragma once

#include <class/StaticImageLoader.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace glimac;

namespace UP
{

struct Button : public StaticImage
{
  GLuint* _texture_hovered;
  GLuint* _texture_clicked;
  bool _isHovered;
  bool _isClicked;
  std::function<void()> _behavior;

  Button()
  : _isClicked(false), _isHovered(false)
  {}
};

/**
 * @brief ButtonLoader Object
 * @brief Create StaticImages for a button
 * @brief Manage the button State ( hover / clicked )
 * @brief Manage the button Behavior
 * 
 */
class ButtonLoader : public StaticImageLoader
{
public:
  /// Constructor and destructor
  
  /**
   * @brief Destroy the Button Loader:: Button Loader object
   * 
   */
  ~ButtonLoader();
  
  /// Methods
  /**
   * @brief Set enabled to False for all the buttons
   * 
   */
  void disable() const;

  /**
   * @brief Get the Button object
   * 
   * @param buttonName 
   * @param file 
   * @param line 
   * @param function 
   * @return Button* 
   */
  Button* getButton(const std::string &buttonName, const char* file, const unsigned int line, const char* function);

  /**
   * @brief Get the Button object
   * 
   * @param buttonName 
   * @param file 
   * @param line 
   * @param function 
   * @return Button* 
   */
  Button* getButton(const std::string &buttonName, const char* file, const unsigned int line, const char* function) const;

  /**
   * @brief Set the buttons to the state hovered
   *
   */
  void mouseHover(const SDL_Event &e) const;
  
  /**
   * @brief Set the buttons to the state Clicked
   *
   */
  void mouseClick() const;
  
  /**
   * @brief Disable the state Clicked
   *
   */
  void mouseUnclick() const;
    
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
  
  /**
   * @brief Setup things for an image :
   * @brief - Vertices of the square
   * @brief - Matrix corresponding of the shape and ratio of the square
   * @brief - IBO
   * 
   * @param filename 
   * @param x 
   * @param y 
   * @param scale 
   * @param img 
   */
  void setupImage(const std::string &filename, const float &x, const float &y, const float &scale, Button *img);
  
  /**
   * @brief Set the Behavior object
   * 
   * @param imageName 
   * @param behavior 
   */
  void setBehavior(const std::string &imageName, const std::function<void()> &behavior) const;
  
  /**
   * @brief Display 1 image
   * 
   * @param imageName
   */
  void displayImage(const std::string &imageName) const;
  // METHODS
};
    
}

#endif 