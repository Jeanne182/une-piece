#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <math.h>
#include <string>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <class/StaticImageLoader.hpp>
#include <class/Model.hpp>

using namespace glimac;
using namespace UP;

main(int argc, char **argv)
{
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 800, "Une Piece");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if (GLEW_OK != glewInitError)
  {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  const FilePath applicationPath(argv[0]);

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/

  Model model(applicationPath.dirPath() + "../../src/assets/models/monkey.obj");

  // Application loop:
  bool done = false;
  while (!done)
  {
    // Event loop:, -1.0f, 0.5f, 0.3f
    SDL_Event e;
    while (windowManager.pollEvent(e))
    {
      if (e.type == SDL_QUIT)
      {
        done = true; // Leave the loop after this iteration
      }
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/

    glClear(GL_COLOR_BUFFER_BIT);
    model.draw();

    // Update the display
    windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}
