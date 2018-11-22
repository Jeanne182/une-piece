#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    
    ShapeVertex()
    {
    };

    ShapeVertex(const glm::vec3& p, const glm::vec3& n, const glm::vec2& c) {
      position = p;
      normal = n;
      texCoords = c;
    };

};
struct Vertex2DUV {
  
  glm::vec2 position;
  glm::vec2 coord;
    
  Vertex2DUV(const glm::vec2 &pos,
                const glm::vec2 &c) {
    position.x = pos.x;
    position.y = pos.y;
    coord.x = c.x;
    coord.y = c.y;
  };
};

}
