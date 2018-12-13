#include <class/App.hpp>
#include <class/Error.hpp>

#include <glimac/FilePath.hpp>

#include <string>
#include <iostream>
#include <exception>
#include <cassert>

namespace UP
{

// =============== SELECT THE LAYOUT ===============
void App::layoutMenu()
{
  buttons.disable();
  _layout = LAYOUT_MENU;

  // Load the images
  try
  {
    staticImages.addImage("Title", -0.85f, 0.9f, 0.4f);
    buttons.addImage("Play", -0.3f, 0.0f, 0.3f);
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
  buttons.setBehavior("Play", [] { std::cout << "LAMBDA of Play" << std::endl; });
  buttons.setBehavior("Scores", [this] { layoutScores(); });
};
void App::layoutScores()
{
  buttons.disable();
  _layout = LAYOUT_SCORES;

  // Load the Images
  try
  {
    buttons.addImage("Scores", -0.5f, 0.9f, 0.3f);
    buttons.addImage("Menu", -0.94f, -0.86f, 0.1f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  buttons.sendVertexBuffer();

  // Set the behaviors
  // TODO
  // Fake behavior to test
  buttons.setBehavior("Scores", [this] { layoutPause(); });
  buttons.setBehavior("Menu", [this] { layoutMenu(); });
};
void App::layoutPause()
{
  buttons.disable();
  _layout = LAYOUT_PAUSE;

  // Load the Images
  try
  {
    staticImages.addImage("Pause", -0.5f, 0.9f, 0.4f);
    buttons.addImage("Resume", -0.5f, -0.25f, 0.25f);
    buttons.addImage("Menu", 0.12f, -0.6f, 0.2f);
    buttons.addImage("Scores", -0.72f, -0.6f, 0.2f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  staticImages.sendVertexBuffer();
  buttons.sendVertexBuffer();

  // Set the behaviors
  buttons.setBehavior("Menu", [this] { layoutMenu(); });
  buttons.setBehavior("Scores", [this] { layoutScores(); });
  buttons.setBehavior("Resume", [] { std::cout << "LAMBDA of Resume" << std::endl; });
};
void App::layoutGame()
{
  buttons.disable();
  _layout = LAYOUT_GAME;

  // TODO
  std::cout << "START THE GAME HERE" << std::endl;
  
};

// =============== GENERIC FACADES FUNCTIONS ===============
void App::draw()
{
  switch (_layout)
  {
  case LAYOUT_MENU:
    drawMenu();
    break;
  case LAYOUT_SCORES:
    drawScores();
    break;
  case LAYOUT_PAUSE:
    drawPause();
    break;
  case LAYOUT_GAME:
    drawGame();
    break;
  default:
    throw Error("No layout Defined", AT);
    break;
  }
};
void App::event(const SDL_Event &e)
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
};

// =============== SPECIFIC FUNCTIONS FOR EACH LAYOUT ===============
void App::drawMenu()
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
};
void App::drawScores()
{
  try
  {
    buttons.displayImage("Scores");
    buttons.displayImage("Menu");
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};
void App::drawPause()
{
  try
  {
    staticImages.displayImage("Pause");
    buttons.displayImage("Resume");
    buttons.displayImage("Menu");
    buttons.displayImage("Scores");
  }
  catch(std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};
void App::drawGame()
{
  try
  {

  }
  catch(std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};

} // namespace UP
