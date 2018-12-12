#include <class/ScoresManager.hpp>
#include <class/Score.hpp>
#include <class/Error.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

namespace UP
{

void ScoresManager::loadScores()
{
  std::ifstream scoresFile(_appPath.dirPath() + "../save/scores");
  if (!scoresFile.is_open())
  {
    throw Error(std::string("Couldn't open the score file: " + _scoresFilename), AT);
  }

  std::string name;
  int score;
  time_t t;
  while (scoresFile >> name >> score >> t)
  {
    addScore(Score(name, score, t));
  }
  scoresFile.close();
}

void ScoresManager::addScore(const Score &s)
{
  _scores.insert(s);
}

void ScoresManager::displayAll() const
{
  std::multiset<Score>::iterator it;
  for (it = _scores.begin(); it != _scores.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void ScoresManager::displayBest(const int n) const
{
  std::multiset<Score>::iterator it;
  int cpt=0;
  for (it=_scores.begin(); it!=_scores.end() && cpt<n; ++it)
  {
    cpt++;
    std::cout << *it << std::endl;
  }
}

void ScoresManager::store() const
{
  std::ofstream scoresFile(_appPath.dirPath() + "../save/scores");
  if (!scoresFile.is_open())
  {
    throw Error(std::string("Couldn't open the score file: " + _scoresFilename), AT);
  }

  std::multiset<Score>::iterator it;
  for (it = _scores.begin(); it != _scores.end(); ++it)
  {
    scoresFile << it->name() << " " << it->score() << " " << it->time() << " ";
  }

  scoresFile.close();
}

} // namespace UP