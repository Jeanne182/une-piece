#include <glimac/glm.hpp>

namespace glimac
{

class Camera
{
public:
  Camera();
  void event(const SDL_Event &e);
  void update();
  void moveFront(const float &t);
  void moveLeft(const float &t);
  void rotateFront(const float &degrees);
  void rotateLeft(const float &degrees);
  glm::mat4 getViewMatrix() const;
  glm::mat4 look(const glm::vec3 &pos) const;

private:
  glm::vec3 _position;    // Position de la camera
  float _fPhi;            // Coord du vecteur sphérique F
  float _fTheta;          // Coord du vecteur sphérique F
  glm::vec3 _frontVector; // Vecteur F
  glm::vec3 _leftVector;  // Vecteur L
  glm::vec3 _upVector;    // Vecteur U

  // End Chargement des textures
  bool KEY_UP_PRESSED = false;
  bool KEY_DOWN_PRESSED = false;
  bool KEY_LEFT_PRESSED = false;
  bool KEY_RIGHT_PRESSED = false;

  void computeDirectionVectors();
};
} // namespace glimac