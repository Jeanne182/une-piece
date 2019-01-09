#include <string>
#include <iostream>
#include <exception>
#include <cassert>
#include <algorithm>
#include <functional>

#include <glimac/FilePath.hpp>

#include <class/App.hpp>
#include <class/AssetManager.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

namespace UP
{

App::App()
    : _staticImages(),
      _buttons(),
      _game(){};

// =============== SELECT THE LAYOUT ===============
void App::layout2D()
{
  AssetManager::Get()->staticImageProgram()._Program.use();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH_TEST);
}
void App::layout3D()
{
  AssetManager::Get()->assetProgramMultiLight()._Program.use();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
}
void App::layoutMenu()
{
  _buttons.disable();
  _layout = LAYOUT_MENU;
  layout2D();

  // Load the images
  try
  {
    _staticImages.addImage("bgMenu", -1.2f, 1.0f, 2.f);
    _staticImages.addImage("Title", -0.85f, 0.8f, 0.4f);
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
  _buttons.setBehavior("Play", [this] { layoutGame(); });
  _buttons.setBehavior("Scores", [this] { layoutScores(); });
};
void App::layoutScores()
{
  _buttons.disable();
  _layout = LAYOUT_SCORES;
  layout2D();

  // Load the Images
  try
  {
    _staticImages.addImage("bgScores", -1.2f, 1.0f, 2.f);
    _buttons.addImage("Scores", -0.5f, 0.9f, 0.3f);
    _buttons.addImage("Menu", -0.94f, -0.86f, 0.1f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _buttons.sendVertexBuffer();

  _buttons.setBehavior("Scores", [this] { layoutPause(); });
  _buttons.setBehavior("Menu", [this] { layoutMenu(); });
};
void App::layoutPause()
{
  _buttons.disable();
  _layout = LAYOUT_PAUSE;
  layout2D();

  // Load the Images
  try
  {
    _staticImages.addImage("bgPause", -1.0f, 1.0f, 2.f);
    _staticImages.addImage("Pause", -0.5f, 0.9f, 0.4f);
    _buttons.addImage("Resume", -0.5f, -0.25f, 0.25f);
    _buttons.addImage("Menu", -0.32f, -0.6f, 0.25f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _staticImages.sendVertexBuffer();
  _buttons.sendVertexBuffer();

  // Set the behaviors
  _buttons.setBehavior("Menu", [this] {
    _game.reset();
    layoutMenu();
  });
  _buttons.setBehavior("Resume", [this] { layoutGame(); });
};
void App::layoutGame()
{
  _buttons.disable();
  layout3D();
  _layout = LAYOUT_GAME;
  std::function<void(const int &)> lambda = [this](const int &score) {
    Score s = Score("Player", score);
    ScoresManager &scores = ScoresManager::Get();
    scores.setPending(s);
    layoutGameOver();
  };
  _game.setGameOverTrigger(lambda);

  layout2D();
  try
  {
    _staticImages.addImage("bonusInvulnerability", 1.f, -1.0f, 50.f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _staticImages.sendVertexBuffer();
};

void App::layoutGameOver()
{
  _buttons.disable();
  _layout = LAYOUT_GAME_OVER;
  layout2D();

  // Load the Images
  try
  {
    _staticImages.addImage("bgGameover", -1.f, 1.0f, 2.f);
    _staticImages.addImage("Gameover", -0.8f, 0.8f, 0.3f);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  // Send the VBO
  _staticImages.sendVertexBuffer();
}

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
  case LAYOUT_GAME_OVER:
    drawGameOver();
    break;
  default:
    throw Error("No layout Defined", AT);
    break;
  }
};

void App::event(const SDL_Event &e)
{
  if (_layout == LAYOUT_GAME)
  {
    _game.event(e);
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
      layoutPause();
    }
  }
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
    case SDL_KEYDOWN:
    {
      int key = e.key.keysym.sym;
      //std::cout << key << ":" << char(key) << std::endl;

      // Shift key handle
      if (key == SDLK_LSHIFT || key == SDLK_RSHIFT)
      {
        SHIFT_PRESSED = true;
      }

      // Delete handle
      if (key == SDLK_BACKSPACE)
      {
        if (_buffer.size() >= 1)
        {
          _buffer.pop_back();
        }
      }

      // Return handle
      if (key == SDLK_RETURN && _layout == LAYOUT_GAME_OVER)
      {
        ScoresManager &scores = ScoresManager::Get();
        scores.getPending().setName(_buffer);
        scores.savePending();
        scores.store();
        layoutScores();
        _buffer = "";
        _game.reset();
      }

      if (key >= SDLK_a && key <= SDLK_z && _buffer.size() < 18)
      {
        // Alphabetic key
        key = SHIFT_PRESSED ? key - 32 : key;
        _buffer += char(key);
      }
    }
    break;
    case SDL_KEYUP:
    {
      const int &key = e.key.keysym.sym;
      // Shift key handle
      if (key == SDLK_LSHIFT || key == SDLK_RSHIFT)
      {
        SHIFT_PRESSED = false;
      }
    }
    } // End switch
  }   // End else
}

// =============== SPECIFIC FUNCTIONS FOR EACH LAYOUT ===============
void App::drawMenu()
{
  try
  {
    _staticImages.displayImage("bgMenu");
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
    AssetManager::Get()->staticImageProgram()._Program.use();
    ScoresManager &scores = ScoresManager::Get();
    TextManager &tm = AssetManager::Get()->textManager();

    _staticImages.displayImage("bgScores");
    _buttons.displayImage("Scores");
    _buttons.displayImage("Menu");
    tm.renderText("Top 10", 300.f, WINDOW_HEIGHT - 220.f, 1.4f, glm::vec3(0.98f, 0.65f, 0.24f));

    std::multiset<Score>::const_iterator it;
    float PADDING_TOP = 250.f;
    float PADDING_LEFT = 100.f;
    float PADDING_RIGHT = 300.f;
    float STRADDING = 46.f;
    float SIZE = 0.8f;

    int cpt = 0;
    for (it = scores.getScores().cbegin(); it != scores.getScores().cend() && cpt < 10; ++it)
    {
      cpt++;
      char userDate[80];
      time_t userTime = it->time();
      strftime(userDate, 80, "%R %D", localtime(&userTime));

      std::string buffer1 = "";
      buffer1 += it->name();
      buffer1 += " : ";
      buffer1 += std::to_string(it->score());

      std::string buffer2 = "";
      buffer2 += "(";
      buffer2 += userDate;
      buffer2 += ")";

      float y = WINDOW_HEIGHT - PADDING_TOP - (cpt * STRADDING);
      float x = PADDING_LEFT;
      tm.renderText(buffer1, x, y, SIZE, glm::vec3(0.97f, 0.93f, 0.02f));
      x = WINDOW_WIDTH - PADDING_RIGHT;
      tm.renderText(buffer2, x, y, SIZE, glm::vec3(0.1f, 0.1f, 0.1f));
    }
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
    _staticImages.displayImage("bgPause");
    _staticImages.displayImage("Pause");
    _buttons.displayImage("Resume");
    _buttons.displayImage("Menu");
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
    layout3D();
    _game.update();
    _game.display();

    layout2D();
    std::string score = std::string("Score : ") + std::to_string(_game.score());
    AssetManager::Get()->textManager().renderText(score, 20.f , 740.0f, 1.f, glm::vec3(1.f, 1.0f, 1.0f));

    _staticImages.displayImage("bonusInvulnerability");
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};

void App::drawGameOver()
{
  try
  {
    AssetManager::Get()->staticImageProgram()._Program.use();
    _staticImages.displayImage("bgGameover");
    _staticImages.displayImage("Gameover");
    std::string underscore;
    if ((SDL_GetTicks() / 700) % 2 == 1)
      underscore += "_";

    AssetManager::Get()->textManager().renderText("Enter your pseudo here :", 150.0f, 400.0f, 1.1f, glm::vec3(1.f, 1.0f, 1.0f));

    float center = WINDOW_WIDTH / 2;
    float x = center - (_buffer.size() * 10.f);
    AssetManager::Get()->textManager().renderText(_buffer + underscore, x, 200.0f, 1.2f, glm::vec3(1.f, 1.0f, 1.0f));
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
    return;
  }
};
} // namespace UP
