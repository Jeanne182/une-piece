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

#include <class/Model.hpp>
#include <class/Utils.hpp>
#include <class/MapManager.hpp>

#include <unistd.h>

using namespace glimac;
using namespace UP;

struct AssetProgram
{
  Program _Program;

  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  std::map<std::string, GLint> uMapTextures;

  AssetProgram(const FilePath &applicationPath) : _Program(loadProgram(
                                                      applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                                      applicationPath.dirPath() + "shaders/normals.fs.glsl"))
  {
    uMVPMatrix = glGetUniformLocation(_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(_Program.getGLId(), "uNormalMatrix");

    // Textures
    GLint uTexture_diffuse1;
    GLint uTexture_specular1;
    uTexture_diffuse1 = glGetUniformLocation(_Program.getGLId(), "uTexture_diffuse1");
    uTexture_specular1 = glGetUniformLocation(_Program.getGLId(), "uTexture_specular1");
    uMapTextures.insert(std::pair<std::string, GLint>(std::string("uTexture_diffuse1"), uTexture_diffuse1));
    uMapTextures.insert(std::pair<std::string, GLint>(std::string("uTexture_specular1"), uTexture_specular1));

    std::map<std::string, GLint>::iterator it;
    for (it = uMapTextures.begin(); it != uMapTextures.end(); it++)
    {
      std::cout << it->first << " : " << it->second << std::endl;
    }
  }
};

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

  //Model model(applicationPath.dirPath() + "../../src/assets/models/nanosuit/nanosuit.obj", assetProgram.uMapTextures);
  Model model(applicationPath.dirPath() + "../../src/assets/models/monkey.obj", assetProgram.uMapTextures);

  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGTH), 0.1f, 100.f);
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

  glEnable(GL_DEPTH_TEST);
  glCheckError();
  // Application loop:
  bool done = false;
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    MVMatrix = glm::scale(glm::translate(glm::mat4(), glm::vec3(0, -3, -5)), glm::vec3(0.3));
    MVMatrix = glm::rotate(MVMatrix, windowManager.getTime() / 2, glm::vec3(0.f, 1.f, 0.f));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(1.0f));

    /* 9_ Envoi des matrices au GPU */
    glUniformMatrix4fv(assetProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(assetProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(assetProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    assetProgram._Program.use();
    model.draw();

    // Update the display
    windowManager.swapBuffers();
    usleep(100000);
  }

  return EXIT_SUCCESS;
}
