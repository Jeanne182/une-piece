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
#include <class/AssetManager.hpp>
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

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  AssetManager::Create(argv);

  /*
  ASSET_PATH = applicationPath.dirPath() + "../../src/assets/";
  std::cout << (ASSET_PATH + "/models/bateau.obj").str() << std::endl;
  assetProgram = new AssetProgram(applicationPath);
  staticImageProgram = new StaticImageProgram(applicationPath);
  */

  App &app = App::Get();
  app.layoutMenu();

  // ============== SCORE MANAGER ==============

  //ScoresManager& scores = ScoresManager::Get(applicationPath);
  //scores.addScore(Score("Paulounet", 66, time(0)));
  //scores.displayAll();
  //scores.store();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
  delete assetProgram;
  delete staticImageProgram;

  return EXIT_SUCCESS;
}
