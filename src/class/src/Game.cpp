#include <class/Game.hpp>
#include <class/Error.hpp>

#include <glimac/FilePath.hpp>

#include <string>
#include <iostream>
#include <exception>
#include <cassert>

namespace UP
{
  
void Game::layoutMenu()
{
  
  // Load the images
  try
  {
    staticImages.addImage("Title", -0.85f, 0.9f, 0.4f);
    buttons.addImage("Play", -0.4f, 0.3f, 0.4f);
    buttons.addImage("Resume", -0.5f, -0.4f, 0.3f);
  } 
  catch ( std::exception& e ) 
  {
    std::cerr << e.what() << std::endl;
  }
  buttons.sendVertexBuffer();
  staticImages.sendVertexBuffer();
}
  
void Game::draw()
{
  switch(_layout)
  {
    case MENU:
      drawMenu();
      break;
    default:
      throw Error("No layout Defined", AT);
      break;
  }
}
  
void Game::drawMenu()
{
  try 
  {
    staticImages.displayImage("Title");
    buttons.displayImage("Play");
    buttons.displayImage("Resume");
  }
  catch ( std::exception& e ) 
  {
    std::cout << e.what() << std::endl;
    return;
  }  
}
  
}