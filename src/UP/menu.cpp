#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include "class/header/ImageLoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glimac;
using namespace UP;

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 800, "Une Piece");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
      std::cerr << glewGetErrorString(glewInitError) << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  
  Assimp::Importer importer;
const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  
  


  // Application loop:
  bool done = false;
  while(!done) {
      // Event loop:
      SDL_Event e;
      while(windowManager.pollEvent(e)) {
          if(e.type == SDL_QUIT) {
              done = true; // Leave the loop after this iteration
          }
      }

      /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/

      // Update the display
      windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}
