#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "maze.h"

//edited by arun
//#include <SDL/SDL.h>
#define PI 3.1415

extern void reshape(int, int);

extern void drawWalls();
extern void drawFloor();

extern void setMaze(int**);

extern void set_maze(Maze);

extern void setMazeSize(int);
extern void renderWorld();
//edited by arun
//extern  void camera(double x, double z, double angleRadians);
//added by arun
Uint32 gameStateTimerFunc(Uint32 interval, void *value);
#endif
