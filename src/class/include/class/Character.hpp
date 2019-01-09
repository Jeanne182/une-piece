#ifndef CHARACTER_UP_HPP__
#define CHARACTER_UP_HPP__

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>

#include <class/Bonus.hpp>
#include <class/GameObject.hpp>
#include <class/Camera.hpp>

using namespace glimac;

namespace UP
{

enum SIDE
{
  LEFT,
  CENTER,
  RIGHT
};

enum VERTICAL
{
  RUNNING,
  JUMPING,
  FALLING
};

class Character : public GameObject
{
public:
  static float MAX_SPEED;
  static const float MAX_JUMP_SPEED;
  static const glm::vec3 GRAVITY;
  static const glm::vec3 JUMP_FORCE;
  // ============= CONSTRUCTORS =============

  /**
   * @brief Construct a new Character object
   *
   */
  Character(Camera &camera);

  /**
   * @brief Destroy the Character object
   *
   */
  ~Character(){};

  // ============= GETTERS =============
  /**
   * @brief Get the Health object
   *
   * @return unsigned int
   */
  inline const int health() const { return _health; }

  /**
   * @brief Get the Last Coordinate object
   *
   * @return const std::vector<int>&
   */
  inline const std::vector<int> &getLastCoordinate() const { return _lastCoordinate; }

  /**
   * @brief Get the Turn Position object
   *
   * @return const std::vector<int>&
   */
  inline const std::vector<int> &getTurnPosition() const { return _turnPosition; }

  /**
   * @brief Get the Direction object
   *
   * @return const int
   */
  inline const int getDirection() const { return _direction; };

  /**
   * @brief
   *
   * @return unsigned int
   */
  inline const unsigned int score() const { return _score * 3 + _cubeCount; }

  /**
   * @brief Get the Side State object
   *
   * @return int
   */
  inline const int getSideState() const { return _sideState; };

  /**
   * @brief Get the Fork Selected object
   *
   * @return true
   * @return false
   */
  inline const bool getForkSelected() const { return _forkSelected; };

  /**
    * @brief Get the Active Bonuses object
    *
    * @return std::map<unsigned int, time_t>
    */
  inline std::map<unsigned int, time_t> getActiveBonuses() const { return _activeBonuses; }

  /**
   * @brief Get the Turn Chosen object
   *
   * @return unsigned int
   */
  inline unsigned int getTurnChosen() { return _turnChosen; };

  /**
   * @brief Get the Scale object
   *
   * @return const float
   */
  inline const float getScale() { return _scale; };

  /**
   * @brief Get the Angles object
   *
   * @return const glm::vec3
   */
  inline const glm::vec3 getAngles() { return _angles; };
  // ============= SETTERS =============

  /**
   * @brief Set the Health object
   *
   * @param health
   */
  inline void setHealth(const unsigned int &health) { _health = health; }

  /**
   * @brief Increase the count of cube run through
   *
   */
  inline void cubeCountIncrease() { _cubeCount++; };

  /**
   * @brief Set the Last Coordinate object
   *
   * @param lastCoordinate
   */
  inline void setLastCoordinate(const std::vector<int> &lastCoordinate) { _lastCoordinate = lastCoordinate; }

  /**
   * @brief Set the turn position object
   *
   * @param turnPosition
   */
  inline void setTurnPosition(const std::vector<int> &turnPosition) { _turnPosition = turnPosition; }

  /**
   * @brief Set the Fork Selected object
   *
   * @param b
   */
  void setForkSelected(const bool &b);

  /**
   * @brief Set the Turn Chosend object
   *
   * @param t
   */
  inline void setTurnChosen(const unsigned int &t) { _turnChosen = t; };

  // ============= MOVEMENT =============
  /**
    * @brief Set the Active Bonuses object
    *
    * @param bonusType, startingTime
    */
  inline void useBonus(const unsigned int &bonusType, const time_t &startingTime) { _activeBonuses.insert(std::make_pair(bonusType, startingTime)); }

  // ============= KEY HANDLER =============

  /**
   * @brief React to a SDL_Event based on the current selected _layout
   *
   * @param e
   */
  void event(const SDL_Event &e);
  /**
   * @brief Handle the Key down SDL event
   *
   * @param key
   */
  void keyDownHandler(const int &key);

  /**
   * @brief Handle the Key up SDL event
   *
   * @param key
   */
  void keyUpHandler(const int &key);

  // =============  MOVEMENT =============
  /**
   * @brief Move the character
   *
   */
  void move();

  /**
   * @brief Modify the _direction vector to turn right
   *
   */
  void turnRight();

  /**
   * @brief Modify the _direction vector to turn left
   *
   */
  void turnLeft();

  /**
   * @brief Increases the speed of the player over time
   *
   */
  void speedUp();

  // =============  GENERIC =============

  /**
   *
   * @brief Compute the MV , MVP and Normal
   *
   * @param cameraView
   */
  void computeMatrix(const glm::mat4 &cameraView);

  // ============= BONUS =============
  /**
   * @brief Add a Bonus to the player
   *
   * @param bonus
   */
  void addBonus(const Bonus &bonus);
  /**
    * @brief Delete a consumed Bonus to the player
    *
    * @param bonus
    */
  void deleteConsumedBonus(const Bonus &bonus);
  /**
     * @brief delete Bonuses of the player that has expired
     *
     */
  void deleteExpiredBonuses();

  // ============= COIN =============
  /**
   * @brief Add a coin to the player score
   *
   * @param coinValue;
   */
  void addCoin(const unsigned int &coinValue);

  // ============= COLLISION =============

  /**
   * @brief Handle the collision for a player : i.e do nothing
   *
   * @param gameObject
   * @return true
   * @return false
   */
  bool collisionHandler(GameObject *gameObject);

  // ============= HEALTH =============
  /**
   * @brief Lose some health
   *
   * @param value
   */
  void loseHealth(const unsigned int &value);

  // ============= MISCELLANEOUS =============

  /**
   * @brief Set the Matrix objectComput the matrixes in a special way for the player
   *
   */
  void updateMatrix();

  /**
   * @brief Update the rotScaleMatrix
   *
   */
  void updateRotScaleMatrix();

  /**
   * @brief Override display
   * 
   */
  void display() const;

private:

  std::vector<int> _lastCoordinate;
  std::vector<int> _turnPosition;

  glm::vec3 _acceleration;

  int _health;
  unsigned int _score;
  unsigned int _cubeCount;
  unsigned int _direction;
  bool _forkSelected;
  unsigned int _turnChosen;

  std::map<unsigned int, time_t> _activeBonuses;

  int _sideState;
  int _verticalState;

  glm::mat4 _rotScaleMatrix;

  bool _smoothRotate;
  glm::vec3 _desiredAngle;

  Camera &_camera;

  // ============= MOVEMENT =============
  /**
   * @brief Move on the side given : LEFT, CENTER, RIGHT
   *
   * @param side
   */
  void sideMove();

  void speedLimiter(glm::vec3 &speed);
  void speedUpdate();
  void applyForce(const glm::vec3 &force);
  void seek(const glm::vec3 &target);

  /**
   * @brief Is called when the character turn after a fork
   *
   */
  void changeMovement();
};

} // namespace UP

#endif
