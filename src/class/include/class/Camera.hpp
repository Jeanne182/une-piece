#ifndef CAMERA_UP_HPP__
#define CAMERA_UP_HPP__

#include <glimac/glm.hpp>

namespace UP
{

/**
 * @brief Act like a Trackball Camera
 * 
 */
class Camera
{
public:
  static const float VIEW_WIDTH;
  /**
   * @brief Construct a new Camera object
   * 
   */
  Camera();

  /**
   * @brief Manage the events of the mouse
   * 
   * @param e 
   */
  void event(const SDL_Event &e);

  /**
   * @brief Update the camera based on the center position
   * 
   * @param center 
   */
  void update(const glm::vec3 &center);

  /**
   * @brief Get the infos from the character
   * 
   */
  void setCharacterInfo(const float &scale, const glm::vec3 &angles);

  /**
   * @brief Get the View Matrix objectSend the view Matrix
   * 
   * @return glm::mat4 
   */
  glm::mat4 getViewMatrix() const;

private:
  glm::vec3 _center;

  // THIRD PERSON MODE
  float _fDistance; // Distane par rapport au centre de la scene
  float _fAngleX;   // Angle X autour de la camera
  float _fAngleY;   // Angle Y autour de la camera

  // FIRST PERSON MODE
  float _fPhi;            // Coord du vecteur sphérique F
  float _fTheta;          // Coord du vecteur sphérique F
  glm::vec3 _frontVector; // Vecteur F
  glm::vec3 _leftVector;  // Vecteur L
  glm::vec3 _upVector;    // Vecteur U

  bool KEY_UP_PRESSED = false;
  bool KEY_DOWN_PRESSED = false;
  bool KEY_LEFT_PRESSED = false;
  bool KEY_RIGHT_PRESSED = false;

  unsigned int _currentPOV;

  /**
   * @brief Translate the camera closer or further to the center
   * 
   * @param delta 
   */
  void TPMoveFront(const float &delta);

  /**
   * @brief Rotate to the left around the center
   * 
   * @param degrees 
   */
  void TPRotateLeft(const float &degrees);

  /**
   * @brief Rotate to the Right around the center
   * 
   * @param degrees 
   */
  void TPRotateRight(const float &degrees);

  /**
 * @brief Move the camera to the front
 * 
 * @param t 
 */
  void FPMoveFront(const float &t);

  /**
   * @brief Move the camera to the left
   * 
   * @param t 
   */
  void FPMoveLeft(const float &t);

  /**
   * @brief Rotate the camera to the front
   * 
   * @param degrees 
   */
  void FPRotateFront(const float &degrees);

  /**
   * @brief Rotate the camera to the left
   * 
   * @param degrees 
   */
  void FPRotateLeft(const float &degrees);

  /**
   * @brief Compute the direction vector
   * 
   */
  void computeDirectionVectors();
};
} // namespace UP

#endif