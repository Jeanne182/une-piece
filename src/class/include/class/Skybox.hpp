#ifndef SKYBOX_UP_HPP__
#define SKYBOX_UP_HPP__

#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>

#include <class/common.hpp>
#include <class/GameObject.hpp>
#include <class/StaticImageLoader.hpp>

using namespace glimac;
namespace UP
{

class Skybox
{

public:
  /**
 * @brief Construct a new Skybox object
 * 
 */
  Skybox();
  /**
   * @brief Destroy the Skybox object
   * 
   */
  ~Skybox();

  /**
   * @brief Display the skybox
   * 
   */
  void display() const;

  void computeMatrix(const glm::mat4 &view);

private:
  GLuint _texture;
  GLuint _vbo, _vao;
  glm::mat4 _V, _P;

  /**
   * @brief Setup the stuff for the cubemap
   * 
   */
  void loadImages();
};

} // namespace UP

#endif