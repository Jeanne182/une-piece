#include <class/Game.hpp>
#include <class/Error.hpp>

#include <glimac/FilePath.hpp>

#include <string>
#include <iostream>
#include <exception>
#include <cassert>

namespace UP
{

// =============== SELECT THE LAYOUT ===============
void Game::layoutMenu()
{
  _layout = LAYOUT_MENU;
  
  // Load the images
  try
  {
    staticImages.addImage("Title", -0.85f, 0.9f, 0.4f);
    buttons.addImage("Play", -0.4f, 0.2f, 0.4f);
    buttons.addImage("Scores", -0.5f, -0.4f, 0.3f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  // Send the VBO
  buttons.sendVertexBuffer();
  staticImages.sendVertexBuffer();

  // Set the behaviors
  buttons.setBehavior("Play", []{ std::cout<<"LAMBDA of Play"<<std::endl; });
  buttons.setBehavior("Scores", []{ std::cout<<"LAMBDA of Scores"<<std::endl; });
}

void Game::layoutScores() 
{
  _layout = LAYOUT_SCORES;
}


// =============== GENERIC FACADES FUNCTIONS ===============
void Game::draw()
{
  switch (_layout)
  {
  case LAYOUT_MENU:
    drawMenu();
    break;
  default:
    throw Error("No layout Defined", AT);
    break;
  }
}

void Game::event(const SDL_Event &e)
{
  switch (_layout)
  {
  case LAYOUT_MENU:
    eventMenu(e);
    break;
  default:
    throw Error("No layout Defined", AT);
    break;
  }
}

// =============== SPECIFIC FUNCTIONS FOR EACH LAYOUT ===============
void Game::drawMenu()
{
  try
  {
    staticImages.displayImage("Title");
    buttons.displayImage("Play");
    buttons.displayImage("Scores");
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
}


void Game::eventMenu(const SDL_Event &e)
{
  switch (e.type)
  {

  case SDL_MOUSEMOTION:
    buttons.mouseHover(e);
  break;

  case SDL_MOUSEBUTTONDOWN:
    buttons.mouseClick();
  break;

  case SDL_MOUSEBUTTONUP:
    buttons.mouseUnclick();
  break;
  }
}

} // namespace UP
