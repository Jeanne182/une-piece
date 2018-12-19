#include <glimac/glm.hpp>

#include <class/Light.hpp>

namespace UP
{

Light::Light()
    : _direction(glm::vec4(-1.f)),
      _intensity(glm::vec4(5.f)){};

} // namespace UP