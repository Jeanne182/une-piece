#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <math.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>

#include <class/common.hpp>
#include <class/StaticImageLoader.hpp>
#include <class/Utils.hpp>
#include <class/Character.hpp>
#include <class/Bonus.hpp>

#include <unistd.h>

using namespace glimac;
using namespace UP;

int main(int argc, char **argv)
{
  // Initialize SDL and open a window
  const int WINDOW_HEIGHT = 800;
  const int WINDOW_WIDTH = 800;
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Une Piece");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError)
  {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  const FilePath applicationPath(argv[0]);
  AssetProgram assetProgram(applicationPath);
  assetProgram._Program.use();

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  Character player(applicationPath.dirPath() + "../../src/assets/models/bateau.obj", assetProgram.uMapTextures);
  Character player2(applicationPath.dirPath() + "../../src/assets/models/bateau.obj", assetProgram.uMapTextures);
  Bonus bonus;
  Bonus bonus1(glm::vec3(0, 0, 0), 1);

  player.addBonus(bonus);
  player.addBonus(bonus1);
  std::map<unsigned int, time_t>::iterator it;
  for (it = player.getActiveBonuses().begin(); it != player.getActiveBonuses().end(); it++)
  {
    std::cout << "Bonus " << it->first << " activé à " << it->second << std::endl;
  }

  std::cout << player.getPosition() << std::endl;
  std::cout << player.getSpeed() << std::endl;
  std::cout << player.getHealth() << std::endl;
  std::cout << player2.getPosition() << std::endl;
  std::cout << player2.getSpeed() << std::endl;
  std::cout << player2.getHealth() << std::endl;

  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

  // Application loop:
  glEnable(GL_DEPTH_TEST);
  bool done = false;
  int test = 0;
  while (!done)
  {
    // Event loop:
    SDL_Event e;
    while (windowManager.pollEvent(e))
    {
      if (e.type == SDL_QUIT)
      {
        done = true; // Leave the loop after this iteration
      }
      switch (e.type)
      {
      case SDL_KEYDOWN:
        /* left/right and up/down player */
        player.keyDownHandler(e.key.keysym.sym);
        break;

      case SDL_KEYUP:
        /* left/right and up/down player */
        player.keyUpHandler(e.key.keysym.sym);
        break;
      }
      switch (e.type)
      {
      case SDL_KEYDOWN:
        /* left/right and up/down player */
        player.keyDownHandler(e.key.keysym.sym);
        break;

      case SDL_KEYUP:
        /* left/right and up/down player */
        player.keyUpHandler(e.key.keysym.sym);
        break;
      }
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //player.staticPosition();
    player.collision(player2);
    if (player.getHealth() == 0)
    {
      std::cout << "You lose" << std::endl;
    }

    player.move();
    player.display(ProjMatrix, MVMatrix, NormalMatrix, assetProgram);
    player.deleteExpiredBonuses();

    // Update the display
    windowManager.swapBuffers();
  }
  //glDeleteBuffers(1, &vbo);
  //glDeleteVertexArrays(1, &vao);
  //glDeleteTextures(1, &MoonMapTex);

  return EXIT_SUCCESS;
}
