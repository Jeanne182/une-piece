#include <class/App.hpp>
#include <class/Error.hpp>

#include <glimac/FilePath.hpp>

#include <string>
#include <iostream>
#include <exception>
#include <cassert>

namespace UP
{

App::App(char **argv, const int &width, const int &height)
    : _appPath(argv[0]),
      _assetProgram(_appPath),
      _buttons(_appPath, width, height),
      _game(Game::Get(_appPath, _assetProgram)),
      _staticImages(_appPath){};

// =============== SELECT THE LAYOUT ===============
void App::layoutMenu()
{
  _buttons.disable();
  _staticImages.useProgram();
  _layout = LAYOUT_MENU;

  // Load the images
  try
  {
    _staticImages.addImage("Title", -0.85f, 0.9f, 0.4f);
    _buttons.addImage("Play", -0.3f, 0.0f, 0.3f);
    _buttons.addImage("Scores", -0.5f, -0.4f, 0.3f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _buttons.sendVertexBuffer();
  _staticImages.sendVertexBuffer();

  // Set the behaviors
  _buttons.setBehavior("Play", [] { std::cout << "LAMBDA of Play" << std::endl; });
  _buttons.setBehavior("Scores", [this] { layoutScores(); });
};
void App::layoutScores()
{
  _buttons.disable();
  _staticImages.useProgram();
  _layout = LAYOUT_SCORES;

  // Load the Images
  try
  {
    _buttons.addImage("Scores", -0.5f, 0.9f, 0.3f);
    _buttons.addImage("Menu", -0.94f, -0.86f, 0.1f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _buttons.sendVertexBuffer();

  // Set the behaviors
  // TODO
  // Fake behavior to test
  _buttons.setBehavior("Scores", [this] { layoutPause(); });
  _buttons.setBehavior("Menu", [this] { layoutMenu(); });
};
void App::layoutPause()
{
  _buttons.disable();
  _staticImages.useProgram();
  _layout = LAYOUT_PAUSE;

  // Load the Images
  try
  {
    _staticImages.addImage("Pause", -0.5f, 0.9f, 0.4f);
    _buttons.addImage("Resume", -0.5f, -0.25f, 0.25f);
    _buttons.addImage("Menu", 0.12f, -0.6f, 0.2f);
    _buttons.addImage("Scores", -0.72f, -0.6f, 0.2f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _staticImages.sendVertexBuffer();
  _buttons.sendVertexBuffer();

  // Set the behaviors
  _buttons.setBehavior("Menu", [this] { layoutMenu(); });
  _buttons.setBehavior("Scores", [this] { layoutScores(); });
  _buttons.setBehavior("Resume", [] { std::cout << "LAMBDA of Resume" << std::endl; });
};
void App::layoutGame()
{
  _buttons.disable();
  _assetProgram._Program.use();
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
  if (_layout == LAYOUT_GAME)
    _game.event(e);
  else
  {
    switch (e.type)
    {
    case SDL_MOUSEMOTION:
      _buttons.mouseHover(e);
      break;

    case SDL_MOUSEBUTTONDOWN:
      _buttons.mouseClick();
      break;

    case SDL_MOUSEBUTTONUP:
      _buttons.mouseUnclick();
      break;
    }
  }
};

// =============== SPECIFIC FUNCTIONS FOR EACH LAYOUT ===============
void App::drawMenu()
{
  try
  {
    _staticImages.displayImage("Title");
    _buttons.displayImage("Play");
    _buttons.displayImage("Scores");
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
    _buttons.displayImage("Scores");
    _buttons.displayImage("Menu");
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
    _staticImages.displayImage("Pause");
    _buttons.displayImage("Resume");
    _buttons.displayImage("Menu");
    _buttons.displayImage("Scores");
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};
void App::drawGame()
{
  try
  {
    _game.update();
    _game.display();
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};

} // namespace UP
