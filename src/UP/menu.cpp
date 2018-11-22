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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glimac;
using namespace UP;

int main(int argc, char **argv)
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
  StaticImageLoader staticImages(applicationPath);
  
  /*
  Assimp::Importer importer;
const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
*/
  // Load the images
  try
  {
    staticImages.addImage(std::string("Title"), -0.8f, 0.8f, 0.4f);
    staticImages.addImage(std::string("Play"), -0.3f, 0.1f, 0.3f);
    staticImages.addImage(std::string("Exit"), -0.3f, -0.3f, 0.3f);
  } 
  catch ( std::exception& e ) 
  {
    std::cerr << e.what() << std::endl;
  }
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
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/

    glClear(GL_COLOR_BUFFER_BIT);
    try 
    {
      staticImages.displayImage(std::string("Exit"));
      staticImages.displayImage(std::string("Play"));
      staticImages.displayImage(std::string("Title"));
    }
    catch ( std::exception& e ) 
    {
      std::cout << e.what() << std::endl;
    }

    // Update the display
    windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}
