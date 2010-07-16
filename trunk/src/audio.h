#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

int initAudio();
Mix_Music* loadAudioFile(const char*);
int playAudio(Mix_Music*,int);
bool isAudioPlaying();
void unloadAudioFile(Mix_Music*);
void stopAll();
void close();
void setAudioPlaying(bool);

#endif
