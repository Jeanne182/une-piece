#ifndef LIGHT_UP_HPP__
#define LIGHT_UP_HPP__

#include <glimac/glm.hpp>

namespace UP
{

/**
 * @brief Store a Light
 * 
 */
class Light
{
public:
  /**
   * @brief Construct a new Light object
   * 
   */
  Light();

  /**
   * @brief Get the direction object
   * 
   * @return const glm::vec4& 
   */
  inline const glm::vec4 &direction() const { return _direction; };

  /**
   * @brief Get the direction object
   * 
   * @return const glm::vec4& 
   */
  inline void setDirection(const glm::vec4 &d) { _direction = d; };

  /**
   * @brief Get the intensity object
   * 
   * @return const glm::vec4& 
   */
  inline const glm::vec4 &intensity() const { return _intensity; };

private:
  glm::vec4 _direction;
  glm::vec4 _intensity;
};
} // namespace UP

#endif
