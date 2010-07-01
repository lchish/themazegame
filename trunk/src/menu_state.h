#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SDL/SDL.h>

int menuInit();
int menuDeInit();
void menuUpdate();
void menuRender();
void menuKeyUp(SDLKey key);
void menuKeyDown(SDLKey key);
#endif
