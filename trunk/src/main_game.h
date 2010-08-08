#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <GL/gl.h> //for GLuint

extern GLuint wall_texture,floor_texture, finish_texture;

extern void setTempMaze(void);
 void reshape(int w, int h);
extern void mainGameUpdate();
extern void myTimer(int);
extern void mainGameKeyboardUp(SDLKey key);
extern void mainGameKeyboardDown(SDLKey key);
extern int mainGameInit();
extern int mainGameDeInit();
extern void mainGameRender();

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
