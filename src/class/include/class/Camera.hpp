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
   * @brief Translate the camera closer or further to the center
   * 
   * @param delta 
   */
  void moveFront(const float &delta);

  /**
   * @brief Rotate to the left around the center
   * 
   * @param degrees 
   */
  void rotateLeft(const float &degrees);

  /**
   * @brief Rotate to the Right around the center
   * 
   * @param degrees 
   */
  void rotateRight(const float &degrees);

  /**
   * @brief Get the View Matrix objectSend the view Matrix
   * 
   * @return glm::mat4 
   */
  glm::mat4 getViewMatrix() const;

private:
  glm::vec3 _center;
  float _fDistance; // Distane par rapport au centre de la scene
  float _fAngleX;   // Angle X autour de la camera
  float _fAngleY;   // Angle Y autour de la camera
  unsigned int _currentPOV;
};
} // namespace UP

#endif
