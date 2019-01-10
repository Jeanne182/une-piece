#ifndef MUSIC_PLAYER_UP_HPP__
#define MUSIC_PLAYER_UP_HPP__

#include <SDL/SDL_mixer.h>

namespace UP
{

class MusicPlayer
{
public:  
  MusicPlayer();
  ~MusicPlayer();
  void playMenu();
  void playGame();
  
private:
  Mix_Music *_game;
  Mix_Music *_menu;
  bool _gamePlaying = true;
};
}

 #endif