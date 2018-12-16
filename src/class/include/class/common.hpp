#ifndef COMMON_HPP__
#define COMMON_HPP__

#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

namespace UP
{

static const bool USE_CHRONO = false;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;

/**
 * @brief Data Structure for a 2D point
 * 
 */
struct Vertex2DUV
{

  glm::vec2 position;
  glm::vec2 coord;

  Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &c)
  {
    position.x = pos.x;
    position.y = pos.y;
    coord.x = c.x;
    coord.y = c.y;
  };
};

/**
 * @brief Data structure for a texture
 * 
 */
struct Texture
{
  unsigned int id;
  std::string type;
  std::string path;
};

/**
 * @brief Data structure to simplify the Coordinates management
 * 
 */
enum COORD
{
  Y,
  X,
  Z
};

} // namespace UP

#endif
