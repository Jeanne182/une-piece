#ifndef SCORES_UP_HPP__
#define SCORES_UP_HPP__

#pragma once

#include <string>
#include <ctime>

namespace UP
{

/**
 * @brief Data structure for a SCORE
 * 
 */
class Score
{
public:
  /**
   * @brief Construct a new Score object
   * 
   * @param name 
   * @param score 
   * @param t 
   */
  Score(const std::string &name, const int &score, const time_t time = std::time(0))
      : _name(name), _score(score), _time(time){};

  /**
   * @brief Getter of the name
   * 
   * @return const std::string 
   */
  inline const std::string name() const { return _name; };

  /**
   * @brief Getter of the score
   * 
   * @return const int 
   */
  inline const int score() const { return _score; };

  /**
   * @brief Getter of the time
   * 
   * @return const time_t 
   */
  inline const time_t time() const { return _time; };

  /**
   * @brief Compare two Scores, for a sorted map
   * 
   * @param s 
   * @return true 
   * @return false 
   */
  bool operator<(const Score &s) const
  {
    return _score > s._score;
  }

  /**
   * @brief Display a Score
   * 
   * @param os 
   * @param s 
   * @return std::ostream& 
   */
  friend std::ostream &operator<<(std::ostream &os, const Score &s)
  {
    char buffer[80];
    strftime(buffer, 80, "%R %D", localtime(&(s._time)));
    os << s._name << ": " << s._score << " | at : " << buffer;
  }

private:
  const std::string _name;
  const int _score;
  const time_t _time;
};

} // namespace UP

#endif