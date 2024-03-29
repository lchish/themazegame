/**
 * Contains all of the audio code required for our game code.
 * Gives us the ability to load ogg files, play them,stop them,
 * pause them etc.
 */

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdio>

#include "audio.h"

static bool audio_playing;
static void musicFinished();
/* Initialises the audio buffers.
 * Make sure you init the audio AFTER the video or else this will not work
 * due to the way SDL initialises itself.
 */
int initAudio(){
  if(SDL_Init(SDL_INIT_AUDIO)!=0){
    fprintf(stderr,"Unable to initialise SDL_mixer %s\n",SDL_GetError());
    return 1;
  }
  int audio_rate = 22050;
  unsigned int audio_format = AUDIO_S16SYS;
  int audio_channels =2;
  int audio_buffers = 4096;
  if(Mix_OpenAudio(audio_rate,audio_format,audio_channels,audio_buffers)!=0){
    fprintf(stderr,"Unable to initialise audio %s\n",Mix_GetError());
    return 1;
  }
  Mix_HookMusicFinished(musicFinished);
  return 0;
}

/* Loads a audio file into main memory.
 * Returns a pointer to the audio
 * NOTE : this can only load ogg vorbis files 
 */
Mix_Music* loadAudioFile(const char *filename){
  Mix_Music *music;
  music = Mix_LoadMUS(filename);
  if(music == NULL){
    fprintf(stderr,"Unable to load Ogg file: %s\n",Mix_GetError());
    return NULL;
  }else{
    return music;
  }
}
/* Plays a audio file that has already been loaded into main mem.
 * If you want infinite looping pass -1 as the number of loops.
 * NOTE: doesn't check if there is audio currently playing.
 */
int playAudio(Mix_Music *audio,int number_of_loops){
  if(Mix_PlayMusic(audio,number_of_loops) == -1){
    fprintf(stderr,"Unable to play Ogg file: %s\n",Mix_GetError());
    return 1;
  }
  audio_playing =true;
  return 0;
}
/*test to see if any audio files are playing*/
bool isAudioPlaying(){
  return audio_playing;
}

/*frees the memory the audio file is using*/
void unloadAudioFile(Mix_Music *audio){
  Mix_FreeMusic(audio);
}

/*called by Mix_HookMusicFinished when the audio stops playing*/
static void musicFinished(){
  audio_playing =false;
}
/*stops all music playing*/
void stopAllAudio(){
  Mix_HaltMusic();
  audio_playing = false;
}
/*closes the SDL_mixer session*/
void closeAudio(){
  Mix_CloseAudio();
}
void setAudioPLaying(bool a){
  audio_playing = a;
}
void pauseAudio(){
  Mix_PauseMusic();
  audio_playing = false;
}
void resumeAudio(){
  Mix_ResumeMusic();
  audio_playing = true;
}
