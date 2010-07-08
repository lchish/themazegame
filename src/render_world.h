#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

//#include <SDL/SDL.h>

extern void reshape(int, int);


extern void init_textures();
extern void free_textures();

extern void drawWalls();
extern void drawFloor();

extern void setMaze(int**);
extern void setMazeSize(int);

extern  void camera(int, int, int);
#endif
