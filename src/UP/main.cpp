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

#include <class/StaticImageLoader.hpp>
#include <class/Program.hpp>
#include <class/Model.hpp>
#include <class/Utils.hpp>
#include <class/chrono.hpp>

#include <unistd.h>

using namespace glimac;
using namespace UP;



main(int argc, char **argv)
{
  // Initialize SDL and open a window
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGTH = 800;
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "Une Piece");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  glCheckError();
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
  
  
  // ============== MODELS ==============
  Model bateau(applicationPath.dirPath() + "../../src/assets/models/bateau.obj", assetProgram.uMapTextures);

  
  // ============== SCORE MANAGER ==============
  ScoresManager& scores = ScoresManager::Get(applicationPath);
  scores.addScore(Score("Paulounet", 66, time(0)));
  scores.displayAll();
  scores.store();
  
  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGTH), 0.1f, 100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

  glEnable(GL_DEPTH_TEST);
  glCheckError();
  float angle = 0.f;
  
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
        done = true; // Leave the loop after this iteration
    }

    /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/
    chr.start();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    angle += 0.05f;
    MVMatrix = glm::scale(glm::translate(glm::mat4(), glm::vec3(0, -3, -5)), glm::vec3(0.3));
    MVMatrix = glm::rotate(MVMatrix,
                           angle,
                           glm::vec3(0.f, 1.f, 0.f));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(1.0f));

        /* 9_ Envoi des matrices au GPU */
    glUniformMatrix4fv(assetProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(assetProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(assetProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    assetProgram._Program.use();
    model.draw();

    // Update the display
    windowManager.swapBuffers();
    chr.stop();
    std::cout << chr.timeSpan() << std::endl;
  }
  return EXIT_SUCCESS;
}
