#ifndef MODEL_UP_HPP__
#define MODEL_UP_HPP__

#pragma once

#include <map>
#include <vector>

#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>

#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>

using namespace glimac;

namespace UP
{
  
enum MENU
{
  MENU
};
/**
    @brief SINGLETON CLASS
*/
class Game
{
public:
  void layoutMenu();
  void draw();
  void event();
  
private:
  static Game instance;
    
  Game() = delete;
  Game(const FilePath &appPath, const int &width, const int &height)
    : _layout(MENU),
    buttons(appPath, width, height),
    staticImages(appPath)
  {};
    
  void drawMenu();
  void evenMenu();
  int _layout;
  const ButtonLoader &buttons;
  const StaticImageLoader &staticImages;
  
public:
  static Game& Get(const FilePath &appPath, const int &width, const int &height)
  {
    static Game instance(appPath, width, height);
    return instance;
  };
  Game(Game const&) = delete;
  void operator=(Game const&) = delete;
};
  
}


#endif