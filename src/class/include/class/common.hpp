#ifndef COMMON_HPP__
#define COMMON_HPP__

#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <string>
#include <map>

using namespace glimac;

namespace UP
{

struct Vertex2DUV
{

  glm::vec2 position;
  glm::vec2 coord;

  Vertex2DUV(const glm::vec2 &pos,const glm::vec2 &c)
  {
    position.x = pos.x;
    position.y = pos.y;
    coord.x = c.x;
    coord.y = c.y;
  };
};

struct Texture
{
  unsigned int id;
  std::string type;
  std::string path;
};

enum COORD
{
  Y,
  X,
  Z
};

} // namespace UP

#endif
