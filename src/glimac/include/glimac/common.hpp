#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include <string>

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
}
