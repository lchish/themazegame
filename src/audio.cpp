#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdio>

#include "audio.h"

static bool audio_playing;
static void musicFinished();
//make sure you init the audio AFTER the video or else this will not work
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
//loads a audio file into main memory
//returns a pointer to the audio
//this can only load ogg vorbis files at the moment
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
//if you want infinite looping pass -1 as the number of loops
int playAudio(Mix_Music *audio,int number_of_loops){
  if(Mix_PlayMusic(audio,number_of_loops) == -1){
    fprintf(stderr,"Unable to play Ogg file: %s\n",Mix_GetError());
    return 1;
  }
  audio_playing =true;
  return 0;
}
//test to see if any audio files are playing
bool isAudioPlaying(){
  return audio_playing;
}

//frees the memory the audio file is using
void unloadAudioFile(Mix_Music *audio){
  Mix_FreeMusic(audio);
}
//called by Mix_HookMusicFinished when the audio stops playing
static void musicFinished(){
  audio_playing =false;
}
//stops all music playing
void stopAllAudio(){
  Mix_HaltMusic();
  audio_playing = false;
}
//closes the SDL_mixer session
void closeAudio(){
  Mix_CloseAudio();
}
void setAudioPLaying(bool a){
  audio_playing = a;
}
