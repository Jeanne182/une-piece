#ifndef BONUS_UP_HPP__
#define BONUS_UP_HPP__

#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include <map>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>

#include <class/GameObject.hpp>

namespace UP
{
static const int BONUS_DURATION = 5;

enum BONUS
{
  INVULNERABILITY,
  SLOWNESS,
  LIFEUP,
  MAGNET
};

class Bonus : public GameObject
{
public:
  // ============= CONSTRUCTORS =============


  /**
   * @brief Construct a new Bonus object
   *
   * @param position
   * @param bonusType
   * @param name
   */
  Bonus(const glm::vec3 position, const unsigned int bonusType, const std::string &name);

  /**
   * @brief Destroy the Bonus object
   *
   */
  ~Bonus(){};

  // ============= METHODS =============
  /**
   * @brief Display the Bonus
   *
   */
  void display() const;
  /**
   * @brief Handle the collision with a player (gameObject dynamic casted)
   *
   */

  bool collisionHandler(GameObject *gameObject);

  /**
   *
   * @brief Compute the MV , MVP and Normal
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);


  // ============= GETTERS =============
  /**
   * @brief Get the Bonus Type object
   *
   * @return unsigned int
   */
  inline unsigned int getBonusType() const { return _bonusType; };
  /**
   * @brief Get the Bonus Duration object
   *
   * @return unsigned int
   */
  inline unsigned int getBonusDuration() const { return _bonusDuration; };

  // ============= SETTERS =============
  /**
   * @brief Set the Bonus Type object
   *
   * @param bonusType
   */
  inline void setBonusType(const unsigned int &bonusType) { _bonusType = bonusType; };

  /*  Bonus Managers */

private:
  // ============= ATTRIBUTES =============
  unsigned int _bonusType;
  unsigned int _bonusDuration;
};

} // namespace UP

#endif
