#include "maze.h"
#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <GL/gl.h> //for GLuint

extern GLuint wall_texture,floor_texture;

//extern void display();
extern void setTempMaze(void);
 void reshape(int w, int h);
extern void idle();
extern void myTimer(int);


//extern Maze maze;

extern void inGameKeyboardUp(SDLKey key);
extern void inGameKeyboardDown(SDLKey key);
extern int gameInit();
extern int gameDeInit();

extern void display();

extern int turning_left_global;
extern int turning_right_global;
extern int moving_fowards_global;

extern int x_position;
extern int y_position;

extern int orientation;

extern int start_x;
extern int start_y;

extern int end_x;
extern int end_y;


#endif