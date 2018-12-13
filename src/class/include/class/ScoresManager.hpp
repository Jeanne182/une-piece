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
  const FilePath &_appPath;

  // ================ SINGLETON's STUFF ==============

public:
  /**
   * @brief Common Getter for the Singleton's Instance
   * 
   */
  static ScoresManager &Get(const FilePath &appPath)
  {
    static ScoresManager instance(appPath);
    return instance;
  };

  // DELETED
  ScoresManager(ScoresManager const &) = delete;
  void operator=(ScoresManager const &) = delete;

private:
  // CONSTRUCTOR
  ScoresManager() = delete;
  ScoresManager(const FilePath &appPath)
      : _appPath(appPath)
  {
    loadScores();
  };
};

} // NAMESPACE UP

#endif
