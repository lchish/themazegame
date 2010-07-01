#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include <SDL/SDL.h>

extern void display();
extern void setTempMaze(void);
extern void reshape(int, int);
extern void idle();
extern void myTimer(int);

void inGameKeyboardUp(SDLKey key);
void inGameKeyboardDown(SDLKey key);
int gameInit();
int gameDeInit();
#endif
