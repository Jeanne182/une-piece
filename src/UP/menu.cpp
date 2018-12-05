#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <math.h>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

using namespace glimac;
using namespace UP;

int main(int argc, char **argv)
{
  // Initialize SDL and open a window
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 800;
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Une Piece");

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
  ButtonLoader buttons(applicationPath, WINDOW_WIDTH, WINDOW_HEIGHT);
  StaticImageLoader staticImages(applicationPath);
  
  // Load the images
  try
  {
    buttons.addImage("Title", -1.f, 1.f, 0.4f);
    staticImages.addImage("Title", -1.f, 1.f, 0.4f);
  } 
  catch ( std::exception& e ) 
  {
    std::cerr << e.what() << std::endl;
  }
  buttons.sendVertexBuffer();
  staticImages.sendVertexBuffer();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
      switch(e.type) {

        case SDL_MOUSEMOTION: {
          buttons.mouseHover(e);
        }
        break;
          
      }
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/

    glClear(GL_COLOR_BUFFER_BIT);
    try 
    {
      buttons.displayImage("Title");
      staticImages.displayImage("Title");
    }
    catch ( std::exception& e ) 
    {
      std::cout << e.what() << std::endl;
      return false;
    }

    // Update the display
    windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}
