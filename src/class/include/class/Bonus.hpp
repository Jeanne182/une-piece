#ifndef BONUS_HPP__
#define BONUS_HPP__

#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <glimac/common.hpp>


namespace UP
{
  #define BONUS_DURATION 5

  enum BONUS {
    INVULNERABILITY,
    SLOWNESS,
    REVIVE,
    MAGNET
  };

class Bonus
{
  public:
    /*  Functions  */
    Bonus();
    Bonus(const glm::vec3 position, const unsigned int bonusType);
    ~Bonus(){}

    /*  Getters  */
    inline glm::vec3 getPosition() const { return _position; }
    inline unsigned int getBonusType() const { return _bonusType; }
    inline unsigned int getBonusDirection() const { return _bonusDuration; }

    /*  Setters  */
    inline void setPosition(const glm::vec3 &position){ _position = position; }
    inline void setBonusType(const unsigned int &bonusType){ _bonusType = bonusType; }

    /*  Bonus Managers */

  private:
    //  Position Data
    glm::vec3 _position;

    // Bonus data
    unsigned int _bonusType;
    unsigned int _bonusDuration;
  };

} // namespace UP

#endif
