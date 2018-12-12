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
#include <class/Character.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

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
   Character player;



   Sphere sphere1(1,32,16);
   Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/tex3D.fs.glsl");
   //std::unique_ptr<Image> MoonMap = loadImage("/home/donadio/Bureau/opengl3/TP1/GLImac-Template/assets/textures/MoonMap.jpg");
   std::unique_ptr<Image> MoonMap = loadImage(applicationPath.dirPath() + "../../src/assets/textures/MoonMap.jpg");
   if(MoonMap == NULL){
     return EXIT_FAILURE;
   }
   program.use();
   GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
   GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
   GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
   GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");

   GLuint MoonMapTex;
   glGenTextures(1, &MoonMapTex);
   glBindTexture(GL_TEXTURE_2D, MoonMapTex);
   glTexImage2D( 	GL_TEXTURE_2D,
   0,
   GL_RGBA,
   MoonMap->getWidth(),
   MoonMap->getHeight(),
   0,
   GL_RGBA,
   GL_FLOAT,
   MoonMap->getPixels());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);

   glEnable(GL_DEPTH_TEST);

   glm::mat4 ProjMatrix;
   glm::mat4 MVMatrix;
   glm::mat4 NormalMatrix;
   ProjMatrix = glm::perspective(glm::radians(70.f), (800/800)*1.f, 0.1f, 100.f);
   MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f,0.f,-5.f));
   NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

   GLuint vbo;
   glGenBuffers(1,&vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sphere1.getVertexCount() * sizeof(ShapeVertex), sphere1.getDataPointer(), GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   GLuint vao;
   glGenVertexArrays(1,&vao);
   glBindVertexArray(vao);


   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal) );
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords) );

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   int nbLunes = 4;
   std::vector<glm::vec3> lunes;
   for(int i =0; i < nbLunes; i++){
     lunes.push_back(glm::sphericalRand(2.f));
   }
   // Application loop:
   bool done = false;
   while(!done) {
      // Event loop:
      SDL_Event e;
      while(windowManager.pollEvent(e)) {
          if(e.type == SDL_QUIT) {
              done = true; // Leave the loop after this iteration
          }
          switch(e.type) {
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

       //player.staticPosition();
       player.move();
        std::cout << player.getPosition() << std::endl;


       //player.verticalMove(1);
       //player.sideMove(1);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glBindVertexArray(vao);

       glBindTexture(GL_TEXTURE_2D, MoonMapTex);
         glUniform1i(uTexture, 0);
         MVMatrix = glm::translate(glm::mat4(1), glm::vec3(1, -3, -5) + glm::vec3(player.getPosY(), 0, player.getPosZ())); // Translation
         MVMatrix = glm::translate(MVMatrix, lunes[0]); // Translation * Rotation * Translation
         MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
         glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
         glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
         glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
         glDrawArrays(GL_TRIANGLES, 0, sphere1.getVertexCount());

         MVMatrix = glm::translate(glm::mat4(1), glm::vec3(-1, 0, -5) - glm::vec3(0, player.getPosX(), 0)); // Translation
         //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(1, 1, 1)); // Translation * Rotation
         MVMatrix = glm::translate(MVMatrix, lunes[1]); // Translation * Rotation * Translation
         MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
         glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
         glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
         glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
         glDrawArrays(GL_TRIANGLES, 0, sphere1.getVertexCount());

         MVMatrix = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, -5) - glm::vec3(0, player.getPosX(), 0)); // Translation
         //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(1, 1, 1)); // Translation * Rotation
         MVMatrix = glm::translate(MVMatrix, lunes[2]); // Translation * Rotation * Translation
         MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
         glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
         glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
         glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
         glDrawArrays(GL_TRIANGLES, 0, sphere1.getVertexCount());

         MVMatrix = glm::translate(glm::mat4(1), glm::vec3(-3, 0, -5) - glm::vec3(0, player.getPosX(), 0)); // Translation
         //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(1, 1, 1)); // Translation * Rotation
         MVMatrix = glm::translate(MVMatrix, lunes[3]); // Translation * Rotation * Translation
         MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
         glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
         glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
         glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
         glDrawArrays(GL_TRIANGLES, 0, sphere1.getVertexCount());

       glBindTexture(GL_TEXTURE_2D, 0);

       glBindVertexArray(0);
      // Update the display
      windowManager.swapBuffers();
   }
   glDeleteBuffers(1, &vbo);
   glDeleteVertexArrays(1, &vao);
   glDeleteTextures(1, &MoonMapTex);

   return EXIT_SUCCESS;
   }
