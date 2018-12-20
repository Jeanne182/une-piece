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
  JUMPING
};

class Character : public GameObject
{
public:
  // ============= CONSTRUCTORS =============

  /**
   * @brief Construct a new Character object
   *
   */
  Character();

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
  inline unsigned int health() const { return _health; }

  /**
   * @brief Get the Last Coordinate object
   * 
   * @return const std::vector<int>& 
   */
  inline const std::vector<int> &getLastCoordinate() const { return _lastCoordinate; }

  /**
   * @brief 
   * 
   * @return unsigned int 
   */
  inline unsigned int score() const { return _score; }

  /**
   * @brief Get the Side State object
   * 
   * @return int 
   */
  inline int getSideState() const { return _sideState; };

  // ============= SETTERS =============
  /**
    * @brief Get the Active Bonuses object
    *
    * @return std::map<unsigned int, time_t>
    */
  inline std::map<unsigned int, time_t> getActiveBonuses() const { return _activeBonuses; }

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
  /**
   * @brief Move the character
   *
   */
  void move();

  /**
   * @brief Display the character
   *
   */
  void display() const;

  /**
   * @brief Reset the Character to default
   *
   */
  void reset();

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
  void addCoin(const unsigned int coinValue);

  // ============= COLLISION =============
  /**
   * @brief Detect a collision and call his solver
   *
   * @param gameObject
   * @return true
   * @return false
   */
  bool collisionDetector(GameObject &gameObject);

  // ============= HEALTH =============
  /**
   * @brief Lose some health
   *
   * @param value
   */
  void loseHealth(const unsigned int &value);

  bool collisionHandler(GameObject *gameObject);

private:
  std::vector<int> _lastCoordinate;
  unsigned int _health;
  unsigned int _score;
  unsigned int _cubeCount;
  int _sideState;
  int _verticalState;
  std::map<unsigned int, time_t> _activeBonuses;

  // ============= MOVEMENT =============
  /**
   * @brief Constantly make the character move forward
   *
   */
  void forwardMove();

  /**
   * @brief Move on the side given : LEFT, CENTER, RIGHT
   *
   * @param side
   */
  void sideMove(const int &side);

  /**
   * @brief Move on the vertical type given : SLIDING, RUNNING, JUMPING
   *
   * @param movement
   */
  void verticalMove(const int &movement);
};

} // namespace UP

#endif
