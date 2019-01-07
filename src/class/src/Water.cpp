#include <class/Water.hpp>

using namespace glimac;

namespace UP
{

Water::Water(const glm::vec3 position, const bool &forkSection)
    : GameObject(position,
                 glm::vec3(0.f, 0.f, 0.f),
                 0.505f,
                 "water.obj"),
      _forkSection(forkSection)
{
  _model->setRepeat(0.2f);
};

void Water::computeMatrix(const glm::mat4 &cameraView)
{
  _MV = cameraView * _M;
  _MVP = MATRIX_PERSPECTIVE * _MV;
  _N = -1.f * glm::transpose(glm::inverse(_MV));
}

bool Water::collisionHandler(GameObject *gameObject)
{
  return false;
}

} // namespace UP
