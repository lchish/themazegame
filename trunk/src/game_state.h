#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL/SDL.h>

#define MENU_STATE_NUMBER 0
#define GAME_STATE_NUMBER 1
extern int CURRENT_STATE;

void set_game_state(const int state_number);
void gameStateUpdate();
void gameStateReshape(int w,int h);
void gameStateKeyboardUp(SDLKey key);
void gameStateKeyboardDown(SDLKey key);
void gameStateRender();
void gameStateFreeAll();
#endif
