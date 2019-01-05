#ifndef SCORES_MANAGER_UP_HPP__
#define SCORES_MANAGER_UP_HPP__

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <ctime>

#include <glimac/FilePath.hpp>

#include <class/Score.hpp>

using namespace glimac;

namespace UP
{

/**
 * @brief Load, add and display scores
 * 
 */
class ScoresManager
{
public:
  /**
 * @brief Load the score file
 * 
 */
  void loadScores();

  /**
   * @brief Add a score to the intern set
   * 
   * @param s 
   */
  void addScore(const Score &s);

  /**
   * @brief Get the Scores object
   * 
   * @return const std::multiset<Score>& 
   */
  inline const std::multiset<Score> &getScores() const
  {
    return _scores;
  }

  /**
   * @brief Get the Pending object
   * 
   * @return Score& 
   */
  inline Score &getPending() { return _pending; };

  /**
   * @brief Set the Pending object
   * 
   * @param s 
   */
  inline void setPending(const Score &s) { _pending = s; };

  /**
   * @brief Save the pending score
   * 
   */
  inline void savePending() { addScore(_pending); };

  /**
   * @brief Display all the scores loaded
   * 
   */
  void displayAll() const;

  /**
   * @brief Display only the 10 best scores
   * 
   * @param n 
   */
  void displayBest(const int n = 10) const;

  /**
   * @brief Store the scores in the persistant file
   * 
   */
  void store() const;

private:
  std::multiset<Score> _scores;
  const std::string _scoresFilename = "scores";
  Score _pending;

  // ================ SINGLETON's STUFF ==============

public:
  /**
   * @brief Common Getter for the Singleton's Instance
   * 
   */
  static ScoresManager &Get()
  {
    static ScoresManager instance;
    return instance;
  };

  // DELETED
  ScoresManager(ScoresManager const &) = delete;
  void operator=(ScoresManager const &) = delete;

private:
  // CONSTRUCTOR
  ScoresManager()
      : _pending("default", 0)
  {
    loadScores();
  };
};

} // NAMESPACE UP

#endif
