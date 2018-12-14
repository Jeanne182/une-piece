#ifndef PROGRAM_UP_HPP__
#define PROGRAM_UP_HPP__

#pragma once

namespace UP
{
  
struct AssetProgram
{
  Program _Program;

  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  std::map<std::string, GLint> uMapTextures;

  AssetProgram(const FilePath &applicationPath) 
    : _Program(loadProgram( 
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
      std::cout << it->first << " : " << it->second << std::endl;
  }
};

}

#endif