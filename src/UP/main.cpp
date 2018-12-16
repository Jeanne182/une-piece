#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <math.h>
#include <string>
#include <unistd.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/TrackballCamera.hpp>

#include <class/App.hpp>
#include <class/Utils.hpp>
#include <class/common.hpp>
#include <class/chrono.hpp>

using namespace glimac;
using namespace UP;

main(int argc, char **argv)
{
  // Initialize SDL and open a window
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Une Piece");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  glCheckError();
  if (GLEW_OK != glewInitError)
  {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/

  App &app = App::Get(argv, WINDOW_WIDTH, WINDOW_HEIGHT);
  app.layoutMenu();
  // ============== SCORE MANAGER ==============

  //ScoresManager& scores = ScoresManager::Get(applicationPath);
  //scores.addScore(Score("Paulounet", 66, time(0)));
  //scores.displayAll();
  //scores.store();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glCheckError(); // We never know
  // Application loop:
  bool done = false;
  Chrono chr;
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

      app.event(e);
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/
    chr.start();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    app.draw();

    // Update the display
    windowManager.swapBuffers();
    //usleep(100000);
    chr.stop();
    if (USE_CHRONO)
      std::cout << chr.timeSpan() << std::endl;
  }

/*
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteTextures(2, textures);
  */

  return EXIT_SUCCESS;
}
