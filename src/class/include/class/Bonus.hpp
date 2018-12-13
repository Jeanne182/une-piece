#ifndef BONUS_HPP__
#define BONUS_HPP__

#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <vector>
#include <map>
#include <glimac/common.hpp>


namespace UP
{

  enum BONUS {
    NONE,
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
    Bonus(glm::vec3 position);
    ~Bonus(){}

    /*  Getters  */
    inline glm::vec3 getPosition() const { return _position; }
    inline glm::vec4 getCurrentBonus() const { return _currentBonus; }

    /*  Setters  */
    inline void setPosition(const glm::vec3 &position){ _position = position; }

    /*  Bonus Managers */
    void addBonus(cont unsigned int bonus);

  private:
    //  Position Data
    glm::vec3 _position;

    // State data
    static glm::vec4 _currentBonus;
  };

} // namespace UP

#endif
