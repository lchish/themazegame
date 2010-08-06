#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "maze.h"

//#include <SDL/SDL.h>
#define PI 3.1415

extern void reshape(int, int);

extern void drawWalls();
extern void drawFloor();

extern void setMaze(int**);

extern void set_maze(Maze);

extern void setMazeSize(int);
extern void renderWorld();
extern  void camera(int, int, int);
void gameStateTimerFunc(int value);

#endif
