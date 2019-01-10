#include <string>

#include <class/MusicPlayer.hpp>
#include <class/AssetManager.hpp>

#include <SDL/SDL_mixer.h>

namespace UP
{

MusicPlayer::MusicPlayer()
{
  /*Ouverture de la musique */
  /* Initialisation de l'API Mixer */
  if((Mix_Init(MIX_INIT_MP3)&MIX_INIT_MP3)!=MIX_INIT_MP3) {
      printf("Mix_Init error: %s\n",Mix_GetError());
  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
      printf("Opening MIX_AUDIO: %s\n", Mix_GetError());
  }
  Mix_VolumeMusic(MIX_MAX_VOLUME/2);

  /* Chargement des musiques */
  _game = Mix_LoadMUS(AssetManager::Get()->musicFile(std::string("game.mp3")).c_str());
  _menu = Mix_LoadMUS(AssetManager::Get()->musicFile(std::string("menu.mp3")).c_str());
}
  

MusicPlayer::~MusicPlayer()
{
  /* Liberation des ressources de la musique */
  Mix_FreeMusic(_game);
  Mix_FreeMusic(_menu);
  Mix_CloseAudio();
}
  
void MusicPlayer::playMenu()
{
  if ( _gamePlaying )
  {
    Mix_PlayMusic(_menu, -1);
    _gamePlaying = false;
  }
}
  
void MusicPlayer::playGame()
{
  if ( !_gamePlaying )
  {
    Mix_PlayMusic(_game, -1);
    _gamePlaying = true;
  }
}
  
} // namespace UP